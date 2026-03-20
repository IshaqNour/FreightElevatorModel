Freight Elevator - Cadmium v2 (ABP-style repository structure)

This repository contains the Freight Elevator model implemented in Cadmium v2.

--------------------------------------------------------------------------------
 Repository structure (mirrors the ABP example)
--------------------------------------------------------------------------------
- atomics/          Atomic DEVS models (ECall, EControl, EVehicle)
- data_structures/  Shared message/type definitions
- input_data/       Input files for experiments/tests
- test/             Stand-alone experiments for atomic models + coupled integration
- top_model/        Coupled models + the top-level simulator (main.cpp)
- vendor/           Optional (kept for consistency with ABP). Not used by default.

The build will generate:
- bin/              Compiled executables
- build/            Object files
- simulation_results/  CSV logs produced by the executables

--------------------------------------------------------------------------------
 Build instructions
--------------------------------------------------------------------------------
This project is designed to run with this folder layout:

    <project_root>/
      cadmium_v2/
      FreightElevatorModel/

`cadmium_v2` and `FreightElevatorModel` must be sibling folders.

1) Prerequisites (If not already in system)
-----------------------------
Install tools once:

    sudo apt update
    sudo apt install -y g++ make cmake git

2) Fresh-clone setup
------------------------------------------------
From an empty folder
   Step 1:
    git clone https://github.com/SimulationEverywhere/cadmium_v2 -b dev-rt 
    git clone https://github.com/IshaqNour/FreightElevatorModel.git

   Step 2:
    cd cadmium_v2
    source build.sh

   Step 3:
    cd ../FreightElevatorModel
    make clean
    make all

3) Run experiments
------------------
Run from `FreightElevatorModel` root.

Atomic model experiments

A1 - ECall (inside call forwarding)
    ./bin/ecall_test input_data/ecall_inside.txt input_data/empty_outside.txt simulation_results/A1_ecall.csv

A2 - ECall (outside call forwarding)
    ./bin/ecall_test input_data/empty_inside.txt input_data/ecall_outside.txt simulation_results/A2_ecall.csv

A3 - ECall (simultaneous inside/outside, inside priority)
    ./bin/ecall_test input_data/ecall_inside.txt input_data/ecall_outside.txt simulation_results/A3_ecall.csv

A4 - EVehicle (delay / travel-time behavior)
    ./bin/evehicle_test input_data/evehicle_single_in.txt simulation_results/A4_evehicle.csv

A5 - EControl (single request)
    ./bin/econtrol_test input_data/econtrol_single_calls.txt input_data/econtrol_single_fback.txt simulation_results/A5_econtrol.csv

A6 - EControl (queued calls / FIFO)
    ./bin/econtrol_test input_data/econtrol_queue_calls.txt input_data/econtrol_queue_fback.txt simulation_results/A6_econtrol.csv

Coupled + integration experiments

C1 - ElevatorCoupled (sequential calls end-to-end)
    ./bin/elevator_test input_data/elevator_calls_test.txt simulation_results/C1_elevator.csv

C2 - ElevatorCoupled (queue behavior / FIFO)
    ./bin/elevator_test input_data/elevator_queue_calls.txt simulation_results/C2_elevator.csv

T1 - FreightElevatorTop (inside calls only)
    ./bin/freight_elevator_top input_data/fe_inside_calls.txt input_data/empty_outside.txt simulation_results/T1_top.csv

T2 - FreightElevatorTop (inside priority at top input)
    ./bin/freight_elevator_top input_data/fe_inside_calls.txt input_data/fe_outside_calls.txt simulation_results/T2_top.csv

4) Output folder
----------------
The makefile creates this automatically, but you can create it manually if needed:

    mkdir -p simulation_results


5) Quick smoke test
-------------------

    make clean && make all && ./bin/elevator_test input_data/elevator_calls_test.txt simulation_results/smoke_elevator.csv

If Cadmium is not in `../cadmium_v2` or `../cadmium`, run:

    make CADMIUM_DIR=/absolute/path/to/cadmium_v2 clean all

6) Documentation included
-------------------------
- FreightElevator.docx
- DVESmodelForm_FreightElevator.docx
