#!/usr/bin/env python3
from __future__ import annotations

import argparse
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[1]
SRC_ROOT = REPO_ROOT / "src"
if str(SRC_ROOT) not in sys.path:
    sys.path.insert(0, str(SRC_ROOT))

from humaneval_pipeline.analysis import run_analysis


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Analyze local benchmark DOE results.")
    parser.add_argument(
        "--config",
        default=str(REPO_ROOT / "config.yaml"),
        help="Path to config YAML.",
    )
    parser.add_argument(
        "--input-csv",
        default=None,
        help="Optional path to summary CSV. Defaults to config.paths.summary_csv.",
    )
    parser.add_argument(
        "--output-dir",
        default=None,
        help="Optional output directory. Defaults to config.paths.analysis_dir.",
    )
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    run_analysis(args.config, input_csv=args.input_csv, output_dir=args.output_dir)


if __name__ == "__main__":
    main()
