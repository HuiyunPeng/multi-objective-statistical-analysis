from __future__ import annotations

from pathlib import Path

from .config import load_config


def run_analysis(
    config_path: str | Path,
    input_csv: str | Path | None = None,
    output_dir: str | Path | None = None,
) -> None:
    try:
        import matplotlib.pyplot as plt
        import pandas as pd
        from statsmodels.formula.api import ols
        from statsmodels.stats.anova import anova_lm
    except ImportError as exc:
        raise RuntimeError(
            "Analysis dependencies are missing. Install requirements.txt before running analysis."
        ) from exc

    config = load_config(config_path)
    summary_path = Path(input_csv).resolve() if input_csv else config.resolve_path(config.paths.summary_csv)
    analysis_dir = Path(output_dir).resolve() if output_dir else config.resolve_path(config.paths.analysis_dir)
    analysis_dir.mkdir(parents=True, exist_ok=True)
    if not summary_path.exists():
        raise FileNotFoundError(f"Summary CSV not found: {summary_path}")

    df = pd.read_csv(summary_path)
    correctness_rates = (
        df.groupby(["objective", "language"], as_index=False)[["correctness_before", "correctness_after"]]
        .mean()
        .rename(
            columns={
                "correctness_before": "baseline_correctness_rate",
                "correctness_after": "optimized_correctness_rate",
            }
        )
    )
    correctness_rates.to_csv(analysis_dir / "correctness_rates.csv", index=False)

    runtime_df = df[
        (df["correctness_before"] == 1)
        & (df["correctness_after"] == 1)
        & df["runtime_improvement_ratio"].notna()
    ].copy()
    memory_df = df[
        (df["correctness_before"] == 1)
        & (df["correctness_after"] == 1)
        & df["memory_improvement_ratio"].notna()
    ].copy()

    _fit_model(
        df=runtime_df,
        response="runtime_improvement_ratio",
        analysis_dir=analysis_dir,
        plt=plt,
        ols=ols,
        anova_lm=anova_lm,
    )
    _fit_model(
        df=memory_df,
        response="memory_improvement_ratio",
        analysis_dir=analysis_dir,
        plt=plt,
        ols=ols,
        anova_lm=anova_lm,
    )
    _plot_correctness(correctness_rates, analysis_dir, plt)


def _fit_model(df, response, analysis_dir, plt, ols, anova_lm) -> None:
    if df.empty:
        (analysis_dir / f"{response}_warning.txt").write_text(
            f"No complete cases available for {response}.\n", encoding="utf-8"
        )
        return

    formula = (
        f"{response} ~ C(problem_id, Sum) + C(objective, Sum) * C(language, Sum)"
    )
    model = ols(formula, data=df).fit()
    anova_table = anova_lm(model, typ=3)
    anova_table.to_csv(analysis_dir / f"{response}_anova.csv")
    (analysis_dir / f"{response}_model_summary.txt").write_text(
        model.summary().as_text(), encoding="utf-8"
    )

    means = (
        df.groupby(["objective", "language"], as_index=False)[response]
        .mean()
        .sort_values(["objective", "language"])
    )
    fig, ax = plt.subplots(figsize=(8, 5))
    for language, group in means.groupby("language"):
        ax.plot(group["objective"], group[response], marker="o", label=language)
    ax.axhline(1.0, color="grey", linewidth=1, linestyle="--")
    ax.set_title(f"Interaction Plot: {response}")
    ax.set_xlabel("Objective")
    ax.set_ylabel(response)
    ax.legend(title="Language")
    fig.tight_layout()
    fig.savefig(analysis_dir / f"{response}_interaction.png", dpi=150)
    plt.close(fig)


def _plot_correctness(correctness_rates, analysis_dir, plt) -> None:
    fig, ax = plt.subplots(figsize=(8, 5))
    for language, group in correctness_rates.groupby("language"):
        ax.plot(
            group["objective"],
            group["optimized_correctness_rate"],
            marker="o",
            label=language,
        )
    ax.set_title("Optimized Correctness Rate by Treatment")
    ax.set_xlabel("Objective")
    ax.set_ylabel("Correctness rate")
    ax.set_ylim(0, 1.05)
    ax.legend(title="Language")
    fig.tight_layout()
    fig.savefig(analysis_dir / "correctness_rates.png", dpi=150)
    plt.close(fig)
