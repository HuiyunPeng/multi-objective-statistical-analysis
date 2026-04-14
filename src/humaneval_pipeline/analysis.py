from __future__ import annotations

import csv
import os
from pathlib import Path

from .config import load_config

SECONDARY_MIN_IMPROVEMENT_RATIO = 1.05
SECONDARY_ANALYSIS_DIRNAME = "secondary_ge_5pct"
ANALYSIS_RESPONSES = (
    "runtime_improvement_ratio",
    "memory_improvement_ratio",
    "memory_area_improvement_ratio",
)


def run_analysis(
    config_path: str | Path,
    input_csv: str | Path | None = None,
    output_dir: str | Path | None = None,
) -> None:
    os.environ.setdefault("PANDAS_NO_USE_NUMEXPR", "1")
    os.environ.setdefault("PANDAS_NO_USE_BOTTLENECK", "1")
    try:
        import matplotlib.pyplot as plt
        import pandas as pd
        from statsmodels.formula.api import ols
        from statsmodels.stats.anova import anova_lm
    except Exception as exc:  # noqa: BLE001
        raise RuntimeError(
            "Analysis dependencies are missing or incompatible. Install requirements.txt with "
            "compatible NumPy/SciPy/statsmodels versions before running analysis."
        ) from exc

    config = load_config(config_path)
    summary_path = Path(input_csv).resolve() if input_csv else config.resolve_path(config.paths.summary_csv)
    analysis_dir = Path(output_dir).resolve() if output_dir else config.resolve_path(config.paths.analysis_dir)
    analysis_dir.mkdir(parents=True, exist_ok=True)
    if not summary_path.exists():
        raise FileNotFoundError(f"Summary CSV not found: {summary_path}")

    df = pd.read_csv(summary_path)
    if df.empty:
        (analysis_dir / "analysis_warning.txt").write_text(
            "Summary CSV is empty.\n",
            encoding="utf-8",
        )
        return

    df["block_id"] = df["language"].astype(str) + "::" + df["task_id"].astype(str)
    include_language = df["language"].nunique() > 1

    correctness_group_cols = ["objective", "prompt_detail"]
    if include_language:
        correctness_group_cols.append("language")

    correctness_rates = (
        df.groupby(correctness_group_cols, as_index=False)[["correctness_before", "correctness_after"]]
        .mean()
        .rename(
            columns={
                "correctness_before": "baseline_correctness_rate",
                "correctness_after": "optimized_correctness_rate",
            }
        )
    )
    correctness_rates.to_csv(analysis_dir / "correctness_rates.csv", index=False)

    metric_frames = {
        response: _complete_cases(df, response)
        for response in ANALYSIS_RESPONSES
        if response in df.columns
    }

    for response, metric_df in metric_frames.items():
        _fit_model(
            df=metric_df,
            response=response,
            analysis_dir=analysis_dir,
            plt=plt,
            ols=ols,
            anova_lm=anova_lm,
            include_language=include_language,
        )
    _plot_correctness(correctness_rates, analysis_dir, plt, include_language)
    _write_secondary_analysis(
        metric_frames=metric_frames,
        analysis_dir=analysis_dir,
        plt=plt,
        ols=ols,
        anova_lm=anova_lm,
        include_language=include_language,
    )


def _complete_cases(df, response):
    return df[
        (df["correctness_before"] == 1)
        & (df["correctness_after"] == 1)
        & df[response].notna()
    ].copy()


def _fit_model(
    df,
    response,
    analysis_dir,
    plt,
    ols,
    anova_lm,
    include_language: bool,
    empty_message: str | None = None,
) -> None:
    warning_path = analysis_dir / f"{response}_warning.txt"
    anova_path = analysis_dir / f"{response}_anova.csv"
    summary_path = analysis_dir / f"{response}_model_summary.txt"
    plot_path = analysis_dir / f"{response}_interaction.png"
    if df.empty:
        warning_path.write_text(
            (empty_message or f"No complete cases available for {response}.") + "\n",
            encoding="utf-8",
        )
        anova_path.unlink(missing_ok=True)
        summary_path.unlink(missing_ok=True)
        plot_path.unlink(missing_ok=True)
        return
    warning_path.unlink(missing_ok=True)

    formula = _analysis_formula(include_language)
    try:
        model = ols(f"{response} ~ {formula}", data=df).fit()
        anova_table = anova_lm(model, typ=3)
        warning_text = ""
    except Exception as exc:  # noqa: BLE001
        if include_language:
            fallback_formula = _analysis_formula(False)
            model = ols(f"{response} ~ {fallback_formula}", data=df).fit()
            anova_table = anova_lm(model, typ=3)
            warning_text = (
                "Fell back to the cpp-style model without an additive language term because "
                f"the multi-language model could not be fit cleanly: {exc}\n"
            )
        else:
            raise

    anova_table.to_csv(anova_path)
    summary_text = model.summary().as_text()
    if warning_text:
        summary_text = warning_text + "\n" + summary_text
    summary_path.write_text(summary_text, encoding="utf-8")

    group_cols = ["objective", "prompt_detail"]
    if include_language:
        group_cols.insert(0, "language")
    means = df.groupby(group_cols, as_index=False)[response].mean()

    fig, ax = plt.subplots(figsize=(9, 5))
    if include_language:
        for (language, prompt_detail), group in means.groupby(["language", "prompt_detail"]):
            ax.plot(
                group["objective"],
                group[response],
                marker="o",
                label=f"{language} | {prompt_detail}",
            )
    else:
        for prompt_detail, group in means.groupby("prompt_detail"):
            ax.plot(group["objective"], group[response], marker="o", label=prompt_detail)
    ax.axhline(1.0, color="grey", linewidth=1, linestyle="--")
    ax.set_title(f"Interaction Plot: {response}")
    ax.set_xlabel("Objective")
    ax.set_ylabel(response)
    ax.legend(title="Condition")
    fig.tight_layout()
    fig.savefig(plot_path, dpi=150)
    plt.close(fig)


def _write_secondary_analysis(metric_frames, analysis_dir, plt, ols, anova_lm, include_language: bool) -> None:
    secondary_dir = analysis_dir / SECONDARY_ANALYSIS_DIRNAME
    secondary_dir.mkdir(parents=True, exist_ok=True)
    (secondary_dir / "filter_notes.txt").write_text(
        "Secondary analysis keeps only correct complete cases with "
        f"improvement_ratio >= {SECONDARY_MIN_IMPROVEMENT_RATIO:.2f} "
        "(at least 5% improvement over baseline for the modeled metric).\n",
        encoding="utf-8",
    )

    summary_rows: list[dict[str, int | float | str]] = []
    for response, metric_df in metric_frames.items():
        filtered_df = metric_df[metric_df[response] >= SECONDARY_MIN_IMPROVEMENT_RATIO].copy()
        summary_rows.append(
            {
                "response": response,
                "min_improvement_ratio": SECONDARY_MIN_IMPROVEMENT_RATIO,
                "input_rows": len(metric_df),
                "kept_rows": len(filtered_df),
                "input_tasks": metric_df["task_id"].nunique(),
                "kept_tasks": filtered_df["task_id"].nunique(),
            }
        )
        _fit_model(
            df=filtered_df,
            response=response,
            analysis_dir=secondary_dir,
            plt=plt,
            ols=ols,
            anova_lm=anova_lm,
            include_language=include_language,
            empty_message=(
                f"No rows met the secondary >=5% improvement filter for {response}."
            ),
        )

    with (secondary_dir / "filter_summary.csv").open("w", encoding="utf-8", newline="") as handle:
        writer = csv.DictWriter(
            handle,
            fieldnames=[
                "response",
                "min_improvement_ratio",
                "input_rows",
                "kept_rows",
                "input_tasks",
                "kept_tasks",
            ],
        )
        writer.writeheader()
        writer.writerows(summary_rows)


def _analysis_formula(include_language: bool) -> str:
    base_formula = "C(block_id, Sum) + C(objective, Sum) * C(prompt_detail, Sum)"
    if include_language:
        return base_formula + " + C(language, Sum)"
    return base_formula


def _plot_correctness(correctness_rates, analysis_dir, plt, include_language: bool) -> None:
    fig, ax = plt.subplots(figsize=(9, 5))
    if include_language:
        for (language, prompt_detail), group in correctness_rates.groupby(["language", "prompt_detail"]):
            ax.plot(
                group["objective"],
                group["optimized_correctness_rate"],
                marker="o",
                label=f"{language} | {prompt_detail}",
            )
    else:
        for prompt_detail, group in correctness_rates.groupby("prompt_detail"):
            ax.plot(
                group["objective"],
                group["optimized_correctness_rate"],
                marker="o",
                label=prompt_detail,
            )
    ax.set_title("Optimized Correctness Rate by Treatment")
    ax.set_xlabel("Objective")
    ax.set_ylabel("Correctness rate")
    ax.set_ylim(0, 1.05)
    ax.legend(title="Condition")
    fig.tight_layout()
    fig.savefig(analysis_dir / "correctness_rates.png", dpi=150)
    plt.close(fig)
