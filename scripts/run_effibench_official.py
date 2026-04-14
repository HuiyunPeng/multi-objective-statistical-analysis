#!/usr/bin/env python3
from __future__ import annotations

import argparse
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[1]
SRC_ROOT = REPO_ROOT / "src"
if str(SRC_ROOT) not in sys.path:
    sys.path.insert(0, str(SRC_ROOT))

from humaneval_pipeline.effibench_official import (
    run_official_effibench_evaluator,
    stage_effibench_results,
    summarize_official_effibench_results,
    write_effibench_summary,
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Run EffiBench's original mprof-based evaluator on an official-format results JSON."
    )
    parser.add_argument(
        "--effibench-root",
        required=True,
        help="Path to a local EffiBench checkout.",
    )
    parser.add_argument(
        "--input-json",
        required=True,
        help="Path to an official-format EffiBench results JSON file.",
    )
    parser.add_argument(
        "--model-name",
        default=None,
        help="Model label to stage under EffiBench/results/. Defaults to the input JSON stem.",
    )
    parser.add_argument(
        "--limit",
        type=int,
        default=None,
        help="Optional number of tasks to evaluate from the front of the JSON file.",
    )
    parser.add_argument(
        "--python-executable",
        default=sys.executable,
        help="Python interpreter whose environment contains mprof.",
    )
    parser.add_argument(
        "--summary-json",
        default=None,
        help=(
            "Optional output path for the summary JSON. Defaults to "
            "results/effibench/official_summaries/manual/<model_name>_summary.json in this repo."
        ),
    )
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    input_json = Path(args.input_json).resolve()
    model_name = args.model_name or input_json.stem
    staged_path, num_tasks = stage_effibench_results(
        input_json=input_json,
        effibench_root=args.effibench_root,
        model_name=model_name,
        limit=args.limit,
    )
    completed = run_official_effibench_evaluator(
        effibench_root=args.effibench_root,
        model_name=model_name,
        python_executable=args.python_executable,
    )
    summary = summarize_official_effibench_results(
        effibench_root=args.effibench_root,
        model_name=model_name,
        num_tasks_requested=num_tasks,
    )
    summary_path = write_effibench_summary(
        summary,
        args.summary_json
        or REPO_ROOT
        / "results"
        / "effibench"
        / "official_summaries"
        / "manual"
        / f"{model_name}_summary.json",
    )

    print(f"Staged results JSON: {staged_path}")
    print(f"Summary JSON: {summary_path}")
    print(f"Tasks requested: {summary.num_tasks_requested}")
    print(f"Tasks measured: {summary.num_tasks_measured}")
    print(f"Normalized runtime: {summary.normalized_execution_time}")
    print(f"Normalized max memory: {summary.normalized_max_memory_usage}")
    print(f"Normalized memory area: {summary.normalized_memory_usage}")
    if completed.stdout.strip():
        print("\nEvaluator stdout:")
        print(completed.stdout.strip())
    if completed.stderr.strip():
        print("\nEvaluator stderr:")
        print(completed.stderr.strip())


if __name__ == "__main__":
    main()
