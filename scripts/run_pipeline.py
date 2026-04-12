#!/usr/bin/env python3
from __future__ import annotations

import argparse
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[1]
SRC_ROOT = REPO_ROOT / "src"
if str(SRC_ROOT) not in sys.path:
    sys.path.insert(0, str(SRC_ROOT))

from humaneval_pipeline.pipeline import STAGE_NAMES, run_pipeline


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Run the HumanEval-X DOE pipeline.")
    parser.add_argument(
        "--config",
        default=str(REPO_ROOT / "config.yaml"),
        help="Path to config YAML.",
    )
    parser.add_argument(
        "--stages",
        default=",".join(STAGE_NAMES),
        help="Comma-separated stages to run: prepare,generate,evaluate,aggregate",
    )
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    stages = [stage.strip() for stage in args.stages.split(",") if stage.strip()]
    run_pipeline(args.config, stages)


if __name__ == "__main__":
    main()
