# HumanEval-X Prompt-Objective DOE Pipeline

This project builds a reproducible command-line experiment pipeline for testing how prompt objective framing affects LLM-based code optimization on HumanEval-X across `python`, `cpp`, and `java`.

The pipeline:

- downloads or loads HumanEval-X for the configured languages
- aligns common `problem_id` values across languages
- uses `prompt + canonical_solution` as the runnable baseline
- generates `runtime`, `memory`, and `balanced` optimization prompts
- calls `gpt-5.4` once per `problem_id × language × objective`
- caches model outputs so reruns do not regenerate completed cases
- runs correctness and benchmark measurements before/after optimization
- writes raw and summary CSV outputs
- fits blocked factorial models with `problem_id` as a fixed-effect block

## Project Structure

```text
README.md
requirements.txt
config.yaml
scripts/
src/
tests/
results/
prompts/
generated_code/
logs/
```

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

The pipeline reads `OPENAI_API_KEY` from `.env` first and falls back to the current shell environment if needed.

3. Confirm local toolchains are available:

```bash
python3 --version
g++ --version
javac -version
java -version
```

## HumanEval-X Notes

HumanEval-X field names differ from a simpler “problem/prompt/tests” assumption in a few important ways:

- `task_id` is language-prefixed, such as `Python/0`, `CPP/0`, and `Java/0`; this pipeline normalizes the shared suffix into `problem_id`
- `prompt` is not a full runnable solution; it already contains the declaration and docstring/scaffold
- `declaration` is the signature-only fragment used here for signature validation
- `canonical_solution` is the baseline solution body appended to `prompt`
- `test` contains the hidden evaluation harness used here for correctness and measurement
- `example_test` exists but is retained only for reference/debugging in v1

## Configuration

Edit [`config.yaml`](/Users/peng397/Desktop/multi-objective-statistical-analysis/config.yaml) to control:

- selected languages
- selected problem IDs
- pilot subset size
- dataset source URLs or local overrides
- model settings
- benchmark repetitions and warmup runs
- per-language timeout limits
- compiler/runtime flags
- output directories

If `dataset.selected_problem_ids` is empty, the pipeline chooses the first `pilot_size` common problem IDs across all configured languages.

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

Override the summary CSV or analysis output directory:

```bash
python3 scripts/analyze_results.py \
  --config config.yaml \
  --input-csv results/analysis_ready.csv \
  --output-dir results/analysis
```

## Outputs

Key artifacts:

- `results/selected_tasks.json`: selected aligned HumanEval-X tasks
- `results/run_manifest.json`: local environment and toolchain versions
- `prompts/<objective>/<language>/<problem_id>.txt`: saved prompts
- `results/raw_responses/<objective>/<language>/<problem_id>.txt`: raw response text
- `results/raw_responses/<objective>/<language>/<problem_id>.json`: raw API response JSON
- `generated_code/baseline/<language>/<problem_id>.<ext>`: baseline source
- `generated_code/optimized/<objective>/<language>/<problem_id>.<ext>`: cleaned optimized code
- `results/evaluations/...`: per-case JSON evaluation records
- `results/raw_runs.csv`: raw measured repetitions
- `results/analysis_ready.csv`: analysis-ready summary table
- `results/analysis/`: ANOVA tables, model summaries, correctness tables, and plots

## CSV Schema

### `results/raw_runs.csv`

One row per measured repetition.

```text
problem_id
task_id
language
objective
variant
repetition_index
runtime_seconds
peak_memory_bytes
returncode
stdout
stderr
correctness_pass
compile_error
test_error
timeout
source_path
```

### `results/analysis_ready.csv`

One row per `problem_id × language × objective`.

```text
problem_id
task_id
language
objective
correctness_before
correctness_after
runtime_before_mean
runtime_after_mean
memory_before_mean
memory_after_mean
runtime_improvement_ratio
memory_improvement_ratio
compile_error
test_error
timeout
compile_error_before
compile_error_after
test_error_before
test_error_after
timeout_before
timeout_after
runtime_before_std
runtime_after_std
runtime_before_cv
runtime_after_cv
memory_before_std
memory_after_std
memory_before_cv
memory_after_cv
baseline_code_path
raw_response_path
raw_response_json_path
cleaned_code_path
prompt_path
signature_valid
model_name
from_cache
```

Improvement ratios are defined as `before / after`, so values greater than `1` indicate improvement.

## Statistical Analysis

The analysis script fits two blocked fixed-effect models on complete cases:

- `runtime_improvement_ratio ~ C(problem_id, Sum) + C(objective, Sum) * C(language, Sum)`
- `memory_improvement_ratio ~ C(problem_id, Sum) + C(objective, Sum) * C(language, Sum)`

It also writes:

- Type III ANOVA tables
- OLS model summaries
- interaction plots for runtime and memory improvement ratios
- correctness-rate tables and plots by `objective × language`

## Language-Specific Manual Adjustment Notes

- Python: the local interpreter version may differ from the HumanEval-X reference environment; the pipeline records the actual version in `results/run_manifest.json`
- C++: some tasks may require different compile or link flags on different systems; adjust `execution.cpp_compile_flags` and `execution.cpp_link_flags` in `config.yaml` if needed
- Java: top-level class names are parsed from the generated source and used as the filename; if a task requires special JVM/compiler flags, edit `execution.java_compile_flags` and `execution.java_runtime_flags`
- Java assertions are enabled by default with `-ea` because HumanEval-style tests commonly rely on `assert`
- Runtime and memory measurement use the provided HumanEval-X `test` harness as the workload; if you later want larger stress workloads, that requires task-specific extensions beyond v1

## Testing

Run the test suite:

```bash
python3 -m unittest discover -s tests
```

The included tests cover:

- `task_id -> problem_id` normalization
- prompt determinism
- model cache key determinism
- response cleaning and signature validation
- Python/C++/Java execution success/failure/timeout paths
- aggregation on synthetic evaluation records
- analysis output generation on synthetic data when `statsmodels` is installed
