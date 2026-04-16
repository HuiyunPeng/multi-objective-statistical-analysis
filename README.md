# C++-First Objective x Prompt-Detail DOE Pipeline

This repository runs reproducible code-optimization experiments over local benchmark datasets.

The main treatment design is:

- `objective ∈ {runtime, memory, balanced}`
- `prompt_detail ∈ {minimal, detailed}`

`language` is chosen in config for each run. The default checked-in configuration uses `cpp` with `benchmark/human_eval_cpp.json`.

## What The Pipeline Does

- selects tasks from a local dataset
- writes baseline code, prompts, raw model responses, cleaned code, and evaluation records to disk
- checks correctness before and after optimization
- benchmarks runtime and memory
- aggregates experiment outputs into CSV tables
- fits blocked analysis models and writes plots, summaries, and filtered secondary analyses

## Setup

Create a virtual environment and install dependencies:

```bash
python3 -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt
```

Create a `.env` file in the project root:

```bash
echo "OPENAI_API_KEY=your_key_here" > .env
```

For the default C++ pipeline, confirm the local toolchain is available:

```bash
python3 --version
g++ --version
```

## HumanEval C++ Dataset

The default dataset is `benchmark/human_eval_cpp.json`.

Each task is expected to include fields such as:

- `task_id`
- `entry_point`
- `function_code`
- `test_code`
- `cpp_stress_test`

Current C++ usage:

- `function_code`: baseline source to optimize
- `test_code`: correctness harness
- `cpp_stress_test`: performance harness
- `entry_point`: used during response cleaning and signature validation

## Configuration

The main config lives in `config.yaml`. The checked-in defaults are:

```yaml
dataset_path: benchmark/human_eval_cpp.json
language: cpp
objectives: [runtime, memory, balanced]
prompt_detail_levels: [minimal, detailed]
selected_task_ids: []
max_tasks:
warmup_runs: 2
num_repetitions: 10
compile_timeout: 20
run_timeout: 20
overwrite_existing: false
```

Notes:

- `selected_task_ids` runs an explicit set of tasks
- `max_tasks` takes the first `N` sorted task IDs when `selected_task_ids` is empty
- leaving both empty runs the full dataset
- `overwrite_existing: false` preserves existing evaluation artifacts when possible
- the full config also includes `model`, `toolchain`, and `paths` blocks

## Running The Main Pipeline

Run all stages:

```bash
python3 scripts/run_pipeline.py --config config.yaml
```

Run a subset of stages:

```bash
python3 scripts/run_pipeline.py --config config.yaml --stages prepare,generate
python3 scripts/run_pipeline.py --config config.yaml --stages evaluate,aggregate
```

Run analysis:

```bash
python3 scripts/analyze_results.py --config config.yaml
```

Override the summary CSV or analysis output directory:

```bash
python3 scripts/analyze_results.py \
  --config config.yaml \
  --input-csv results/analysis_ready.csv \
  --output-dir results/analysis
```

## EffiBench Pipeline

The EffiBench workflow uses `config_effibench.yaml` and writes its artifacts under `results/effibench/`, `prompts/effibench/`, and `generated_code/effibench/`.

Before running it, point `dataset_path` in `config_effibench.yaml` at your local EffiBench checkout. The current workflow supports:

- `language: python`
- difficulty filtering through `selected_difficulty_levels`
- the official EffiBench `mprof`-based evaluator

Run the full EffiBench pipeline and then analyze it:

```bash
python3 scripts/run_effibench_pipeline.py --config config_effibench.yaml
python3 scripts/analyze_results.py --config config_effibench.yaml
```

Run the official evaluator directly on an official-format results JSON:

```bash
python3 scripts/run_effibench_official.py \
  --effibench-root /path/to/EffiBench \
  --input-json /path/to/results/model.json \
  --python-executable /path/to/python
```

The selected Python environment must have `memory_profiler` installed so `mprof` is available.

## Bundled Results Archive

The repo root also includes `results.tar`, which packages the archived `results/` tree for both benchmark tracks:

- HumanEval: raw outputs, aggregated CSVs, and analysis artifacts
- EffiBench: raw outputs, aggregated CSVs, and analysis artifacts for the 30 selected `Hard` problems in the checked-in configuration

You can extract it with:

```bash
tar -xf results.tar
```

## Artifact Layout

Main outputs for the default pipeline:

- `results/selected_tasks.json`: selected task manifest
- `results/run_manifest.json`: environment and toolchain snapshot
- `prompts/<objective>/<prompt_detail>/<language>/<task_id>.txt`: saved prompts
- `results/raw_responses/<objective>/<prompt_detail>/<language>/<task_id>.txt`: raw response text
- `results/raw_responses/<objective>/<prompt_detail>/<language>/<task_id>.json`: raw API response payload
- `results/generation_metadata/<objective>/<prompt_detail>/<language>/<task_id>.json`: prompt and response bookkeeping
- `generated_code/baseline/<language>/<task_id>.<ext>`: baseline source
- `generated_code/optimized/<objective>/<prompt_detail>/<language>/<task_id>.<ext>`: cleaned optimized code
- `results/evaluations/...`: per-case evaluation records
- `results/raw_runs.csv`: raw benchmark measurements
- `results/analysis_ready.csv`: analysis-ready summary table
- `results/analysis/`: model summaries, ANOVA tables, plots, and correctness summaries
- `results/analysis/secondary_ge_5pct/`: secondary filtered analysis for complete correct cases with metric-specific `improvement_ratio >= 1.05`

## Summary Table

`results/analysis_ready.csv` contains one row per `task_id x objective x prompt_detail` and includes fields such as:

- `task_id`
- `language`
- `objective`
- `prompt_detail`
- `correctness_before`
- `correctness_after`
- `runtime_before_mean_ms`
- `runtime_after_mean_ms`
- `memory_before_mean`
- `memory_after_mean`
- `runtime_improvement_ratio`
- `memory_improvement_ratio`
- `compile_error`
- `test_error`
- `timeout`
- `prompt_path`
- `raw_response_path`
- `cleaned_code_path`

Improvement ratios are defined as `before / after`, so values greater than `1` indicate improvement.

## Analysis Model

For C++-only runs, the analysis uses blocked fixed-effect models of the form:

- `response ~ C(block_id, Sum) + C(objective, Sum) * C(prompt_detail, Sum)`

When multiple languages appear in the summary CSV, the analysis attempts to add:

- `+ C(language, Sum)`

This keeps `language` as a blocking term rather than part of the main treatment interaction.
