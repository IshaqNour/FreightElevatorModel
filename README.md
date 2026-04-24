# Freight Elevator Model

This repository contains a Cadmium DEVS model of a freight elevator system. The
model logic is organized into atomic components for call handling, control, and
vehicle movement, plus coupled models that connect those parts into the full
system.

## Project Layout

`atomics/`
Core DEVS atomic models:
- `ecall.hpp`
- `econtrol.hpp`
- `evehicle.hpp`

`top_model/`
Coupled models and the full-system simulator entry point:
- `elevator_coupled.hpp`
- `freight_elevator_top.hpp`
- `experiment.hpp`
- `main.cpp`

`test/`
Standalone drivers for the individual atomic models and the coupled elevator test:
- `main_ecall_test.cpp`
- `main_econtrol_test.cpp`
- `main_evehicle_test.cpp`
- `main_elevator_test.cpp`

`input_data/`
Input trajectories used by the test drivers and full-system run.

`scripts/`
Bash launch scripts for each simulation:
- `run_ecall.sh` -> Generates `A1_ecall.csv`, `A2_ecall.csv`, and `A3_ecall.csv`
- `run_evehicle.sh` -> Generates `A4_evehicle.csv`
- `run_econtrol.sh` -> Generates `A5_econtrol.csv` and `A6_econtrol.csv`
- `run_elevator.sh` -> Generates `C1_elevator.csv` and `C2_elevator.csv`
- `run_freight_elevator.sh` -> Generates `T1_top.csv` and `T2_top.csv`
- `run_all_experiments.sh` -> Generates all

`simulation_results/`
Generated CSV logs from each run.

`bin/` and `build/`
Created automatically during compilation.

## Supported Environment
- WSL Ubuntu on Windows
- Git Bash or another bash environment only if `make`, `g++`, and `bash` are all already on `PATH`
- Linux

The recommended Windows setup is WSL Ubuntu, not native PowerShell or Command
Prompt.

## Cadmium Setup

The `makefile` resolves Cadmium through a variable:

```makefile
INCLUDECADMIUM=-I $(CADMIUM)
```

In case the `CADMIUM` variable is not picked up in WSL and results in "input files" error, then manually set `CADMIUM` in WSL so it points to the `cadmium_v2/include` directory:

```bash
export CADMIUM=/mnt/c/.../path/to/cadmium_v2/include
echo $CADMIUM
```

## WSL Workflow (preffered run flow)

This is the recommended Windows workflow.

Install the required packages once in Ubuntu/WSL:

```bash
sudo apt update
sudo apt install -y build-essential git
```

If the repositories are already on your Windows drive, open WSL and enter the
repo through `/mnt/c/...`:

```bash
cd /mnt/c/Users/.../FreightElevatorModel
```

Run every documented experiment in one command:

```bash
cd /mnt/c/Users/.../FreightElevatorModel
./scripts/run_all_experiments.sh
ls simulation_results
```

Run the experiment scripts one by one:

```bash
cd /mnt/c/Users/.../FreightElevatorModel

./scripts/run_ecall.sh
cat simulation_results/A1_ecall.csv
cat simulation_results/A2_ecall.csv
cat simulation_results/A3_ecall.csv

./scripts/run_evehicle.sh
cat simulation_results/A4_evehicle.csv

./scripts/run_econtrol.sh
cat simulation_results/A5_econtrol.csv
cat simulation_results/A6_econtrol.csv

./scripts/run_elevator.sh
cat simulation_results/C1_elevator.csv
cat simulation_results/C2_elevator.csv

./scripts/run_freight_elevator.sh
cat simulation_results/T1_top.csv
cat simulation_results/T2_top.csv
```

## Bash Workflow

Use this section if you are already in Linux or in a bash environment where
`make`, `g++`, and `bash` are available on `PATH`.

Clone and build:

```bash
git clone https://github.com/SimulationEverywhere/cadmium_v2 -b dev-rt
git clone https://github.com/IshaqNour/FreightElevatorModel.git
cd FreightElevatorModel
make clean
make
```

Run all experiments:

```bash
bash scripts/run_all_experiments.sh
ls simulation_results
```

Run the scripts one by one:

```bash
bash scripts/run_ecall.sh
bash scripts/run_evehicle.sh
bash scripts/run_econtrol.sh
bash scripts/run_elevator.sh
bash scripts/run_freight_elevator.sh
```

Check outputs:

```bash
cat simulation_results/A1_ecall.csv
cat simulation_results/A2_ecall.csv
cat simulation_results/A3_ecall.csv
cat simulation_results/A4_evehicle.csv
cat simulation_results/A5_econtrol.csv
cat simulation_results/A6_econtrol.csv
cat simulation_results/C1_elevator.csv
cat simulation_results/C2_elevator.csv
cat simulation_results/T1_top.csv
cat simulation_results/T2_top.csv
```

## Output Format

For the clearest view of the output, print the CSV file in the terminal:

```bash
cat simulation_results/T2_top.csv
```

## Included Documents

- `FreightElevator.docx`
- `DVESmodelForm_FreightElevator.docx`

