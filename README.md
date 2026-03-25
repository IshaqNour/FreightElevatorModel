# Freight Elevator Model

This repository contains a Cadmium DEVS model of a freight elevator system. The model logic is organized into atomic components for call handling, control, and vehicle movement, plus coupled models that connect those parts into the full system.

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
- `run_ecall.sh`
- `run_econtrol.sh`
- `run_evehicle.sh`
- `run_elevator.sh`
- `run_freight_elevator.sh`

`simulation_results/`
Generated text logs from each run.

`bin/` and `build/`
Created automatically during compilation.

## Build Assumption

This repo expects `cadmium_v2` to sit beside `FreightElevatorModel` in the parent folder:

```text
A1Test/
|- cadmium_v2/
|- FreightElevatorModel/
```

The `makefile` includes Cadmium from:

```makefile
INCLUDECADMIUM=-I ../cadmium_v2/include
```

If your Cadmium folder is somewhere else, update that line in the [makefile](/c:/Users/ishaq/Documents/SYSC4906G/A1Test/FreightElevatorModel/makefile).

## Running the Model

Each script follows the same flow:
1. `make clean`
2. `make`
3. run one executable
4. redirect the simulator output into `simulation_results/*.txt`

### PowerShell

From the repo root:

```powershell
cd C:\Users\ishaq\Documents\SYSC4906G\A1Test\FreightElevatorModel
```

Run the full system:

```powershell
bash scripts/run_freight_elevator.sh
cat simulation_results/freight_elevator_output.txt
```

Run the individual experiments:

```powershell
bash scripts/run_ecall.sh
cat simulation_results/ecall_output.txt

bash scripts/run_econtrol.sh
cat simulation_results/econtrol_output.txt

bash scripts/run_evehicle.sh
cat simulation_results/evehicle_output.txt

bash scripts/run_elevator.sh
cat simulation_results/elevator_output.txt
```

### Linux

```bash
./scripts/run_freight_elevator.sh
./scripts/run_ecall.sh
./scripts/run_econtrol.sh
./scripts/run_evehicle.sh
./scripts/run_elevator.sh
```

## Output Format
For the clearest view of the output, please print the file in the terminal:

```bash
cat simulation_results/freight_elevator_output.txt
```

## Included Documents

- `FreightElevator.docx`
- `DVESmodelForm_FreightElevator.docx`
