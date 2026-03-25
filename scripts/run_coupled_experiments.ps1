$runner = Join-Path $PSScriptRoot "run_freight_experiment.ps1"

& $runner -Executable "bin/elevator_test" -Arguments @(
    "input_data/elevator_calls_test.txt",
    "simulation_results/C1_elevator.csv"
)

& $runner -Executable "bin/elevator_test" -Arguments @(
    "input_data/elevator_queue_calls.txt",
    "simulation_results/C2_elevator.csv"
)
