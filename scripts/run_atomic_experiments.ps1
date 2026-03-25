$runner = Join-Path $PSScriptRoot "run_freight_experiment.ps1"

& $runner -Executable "bin/ecall_test" -Arguments @(
    "input_data/ecall_inside.txt",
    "input_data/empty_outside.txt",
    "simulation_results/A1_ecall.csv"
)

& $runner -Executable "bin/ecall_test" -Arguments @(
    "input_data/empty_inside.txt",
    "input_data/ecall_outside.txt",
    "simulation_results/A2_ecall.csv"
)

& $runner -Executable "bin/ecall_test" -Arguments @(
    "input_data/ecall_inside.txt",
    "input_data/ecall_outside.txt",
    "simulation_results/A3_ecall.csv"
)

& $runner -Executable "bin/evehicle_test" -Arguments @(
    "input_data/evehicle_single_in.txt",
    "simulation_results/A4_evehicle.csv"
)

& $runner -Executable "bin/econtrol_test" -Arguments @(
    "input_data/econtrol_single_calls.txt",
    "input_data/econtrol_single_fback.txt",
    "simulation_results/A5_econtrol.csv"
)

& $runner -Executable "bin/econtrol_test" -Arguments @(
    "input_data/econtrol_queue_calls.txt",
    "input_data/econtrol_queue_fback.txt",
    "simulation_results/A6_econtrol.csv"
)
