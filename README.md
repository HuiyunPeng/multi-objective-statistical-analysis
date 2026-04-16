# C++-First Objective × Prompt-Detail DOE Pipeline

This project runs a reproducible code-optimization experiment over a local benchmark dataset. The default pipeline is centered on C++ and the local file `benchmark/human_eval_cpp.json`.

The main factorial design is:

- `objective ∈ {runtime, memory, balanced}`
- `prompt_detail ∈ {minimal, detailed}`

`language` is now a configuration/block field rather than a main treatment factor. The default active language is `cpp`.

## What The Pipeline Does

- loads a local benchmark JSON file for the selected language
- uses each task's `function_code` as the baseline code to optimize
- generates six prompt variants from `objective × prompt_detail`
- saves every prompt, raw response, and cleaned code artifact to disk
- validates correctness with `test_code`
- benchmarks C++ performance with `cpp_stress_test`
- measures repeated runtime and memory usage before and after optimization
- writes raw and summary CSV outputs
- fits blocked analysis models over `objective`, `prompt_detail`, and their interaction

## Dataset Format

The default dataset is `benchmark/human_eval_cpp.json`.

Each task is expected to contain fields such as:

- `task_id`
- `entry_point`
- `function_code`
- `test_code`
- `stress_test`
- `cpp_stress_test`

Field usage in the current C++ pipeline:

- `function_code`: original code to optimize
- `test_code`: correctness harness
- `cpp_stress_test`: C++ performance harness
- `stress_test`: retained in the data model for future language support, but not preferred for C++ when `cpp_stress_test` exists
- `entry_point`: used during response cleaning / signature validation

## Setup

1. Create a virtual environment and install dependencies:

```bash
python3 -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt
```

2. Create a `.env` file in the project root:

```bash
echo "OPENAI_API_KEY=your_key_here" > .env
```

3. Confirm the local C++ toolchain is available:

```bash
python3 --version
g++ --version
```

## Configuration

The main config lives in `config.yaml`. The default shape is:

```yaml
dataset_path: benchmark/human_eval_cpp.json
language: cpp
objectives: [runtime, memory, balanced]
prompt_detail_levels: [minimal, detailed]
selected_task_ids: []
max_tasks:
warmup_runs: 1
num_repetitions: 5
compile_timeout: 20
run_timeout: 20
```

Notes:

- `selected_task_ids` is the explicit task list; if you set it, those tasks are used as-is
- `max_tasks` lets you run the first `N` tasks after sorting by `task_id`; it is only used when `selected_task_ids` is empty
- leaving both `selected_task_ids` and `max_tasks` empty means "run all tasks in the dataset"
- `warmup_runs` controls unmeasured benchmark executions before timing/memory samples are collected
- `num_repetitions` controls how many measured benchmark samples are collected after warmup
- `language` is currently wired end-to-end for `cpp`
- the structure is designed so future datasets like `benchmark/human_eval_python.json` can be added with a new harness implementation

## Running The Pipeline

Run the full pipeline:

```bash
python3 scripts/run_pipeline.py --config config.yaml
```

Run specific stages:

```bash
python3 scripts/run_pipeline.py --config config.yaml --stages prepare,generate
python3 scripts/run_pipeline.py --config config.yaml --stages evaluate,aggregate
```

Run the analysis step:

```bash
python3 scripts/analyze_results.py --config config.yaml
```

Run the EffiBench optimization pipeline with GPT-5.4 generation and EffiBench's official
`mprof`-based evaluator:

```bash
python3 scripts/run_effibench_pipeline.py --config config_effibench.yaml
python3 scripts/analyze_results.py --config config_effibench.yaml
```

Notes for EffiBench:

- `config_effibench.yaml` can point at EffiBench's richer `data/dataset_with_difficulty_and_algorithm.json` file if you want difficulty-aware slices such as `Hard`
- `selected_difficulty_levels` filters the dataset before `max_tasks`; for example, `selected_difficulty_levels: [Hard]` and `max_tasks: 10` runs the first 10 hard problems
- the configured Python executable should point to an environment with `memory_profiler` installed so `mprof` is available
- the EffiBench pipeline writes its own artifacts under `results/effibench/`, `prompts/effibench/`, and `generated_code/effibench/`
- EffiBench analysis includes the same blocked model used for HumanEval and adds `memory_area_improvement_ratio` when present

Run EffiBench's original `mprof`-based evaluator on an official-format results JSON:

```bash
python3 scripts/run_effibench_official.py \
  --effibench-root /path/to/EffiBench \
  --input-json /path/to/results/gpt-3.5-turbo.json \
  --python-executable /path/to/python
```

Notes:

- The selected Python environment must have `memory_profiler` installed so `mprof` is available on `PATH`
- The input JSON must follow EffiBench's official result format and include fields such as `problem_idx`, `completion`, `canonical_solution`, `small_test_cases`, and `test_case`
- The script stages the JSON under `EffiBench/results/`, runs `code_efficiency_calculator.py`, and writes a summary JSON under `results/effibench/official_summaries/manual/`

Override the summary CSV or analysis output directory:

```bash
python3 scripts/analyze_results.py \
  --config config.yaml \
  --input-csv results/analysis_ready.csv \
  --output-dir results/analysis
```

## Artifact Layout

Key outputs:

- `results/selected_tasks.json`: selected task manifest for the active language
- `results/run_manifest.json`: local environment and toolchain versions
- `prompts/<objective>/<prompt_detail>/<language>/<task_id>.txt`: saved prompts
- `results/raw_responses/<objective>/<prompt_detail>/<language>/<task_id>.txt`: raw response text
- `results/raw_responses/<objective>/<prompt_detail>/<language>/<task_id>.json`: raw API response JSON
- `generated_code/baseline/<language>/<task_id>.<ext>`: baseline source
- `generated_code/optimized/<objective>/<prompt_detail>/<language>/<task_id>.<ext>`: cleaned optimized code
- `results/evaluations/...`: per-case evaluation JSON records
- `results/raw_runs.csv`: raw measured repetitions
- `results/analysis_ready.csv`: analysis-ready summary table
- `results/analysis/`: ANOVA tables, model summaries, correctness tables, and plots
- `results/analysis/secondary_ge_5pct/`: secondary ANOVA tables and plots restricted to `improvement_ratio >= 1.05`

## Output Columns

`results/analysis_ready.csv` contains one row per `task_id × objective × prompt_detail` and includes columns such as:

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
The analysis step also writes a secondary filtered analysis under `results/analysis/secondary_ge_5pct/`
that keeps only correct complete cases with metric-specific `improvement_ratio >= 1.05`.

## Analysis Model

For cpp-only runs, the analysis uses blocked fixed-effect models of the form:

- `response ~ C(block_id, Sum) + C(objective, Sum) * C(prompt_detail, Sum)`

When multiple languages appear in the summary CSV later, the analysis will attempt to add:

- `+ C(language, Sum)`

while still keeping language out of the main treatment interaction.

## Manual Adjustment Notes

- C++ performance measurement currently prefers `cpp_stress_test`; adjust your dataset if a task needs a different benchmark harness
- Some tasks may require different compiler or link flags; adjust `toolchain.cpp_compile_flags` or `toolchain.cpp_link_flags` in `config.yaml`
- Analysis dependencies may need manual version alignment. The current environment showed a NumPy/SciPy/statsmodels compatibility issue, so you may need to reinstall those packages together before running `scripts/analyze_results.py`

## Extension Path

The refactor is intentionally C++-first, but the code is organized so future language support can be added by introducing:

- a language-specific dataset mapping
- a prompt/display name mapping
- a harness implementation for correctness and performance execution
- any language-specific stress-test field selection
