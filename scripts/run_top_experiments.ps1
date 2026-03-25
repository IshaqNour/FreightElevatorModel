$runner = Join-Path $PSScriptRoot "run_freight_experiment.ps1"

& $runner -Executable "bin/freight_elevator_top" -Arguments @(
    "input_data/fe_inside_calls.txt",
    "input_data/empty_outside.txt",
    "simulation_results/T1_top.csv"
)

& $runner -Executable "bin/freight_elevator_top" -Arguments @(
    "input_data/fe_inside_calls.txt",
    "input_data/fe_outside_calls.txt",
    "simulation_results/T2_top.csv"
)
