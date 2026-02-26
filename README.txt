Freight Elevator (Cadmium) — Build & Experimentation Instructions
==========================================================

This repository contains atomic DEVS models (ECall, EVehicle, EControl) and the coupled models
(ElevatorCoupled, FreightElevatorTop). All experiments log a CSV trace using Cadmium's CSVLogger.

Note: You need to add the cadmium repo 
Step1:
git clone https://github.com/SimulationEverywhere/cadmium_v2 -b dev-rt

Step 2:
cd cadmium_v2

Step 3:
source build.sh

1) Build
--------
From the repository root:

    make clean
    make all

Or build a specific executable:

    make bin/ecall_test
    make bin/evehicle_test
    make bin/econtrol_test
    make bin/elevator_test
    make bin/freight_elevator_top

Note:
- The Makefile clean target may delete the simulation_results/ directory. If you want to keep old CSV
  outputs, either re-create the folder after clean, or remove simulation_results from the clean target.

2) Output folder
----------------
Create the output folder once (if it does not already exist):

    mkdir -p simulation_results

3) Running the experiments (Part III)
-------------------------------------

General pattern (run from repository root):

    ./bin/<executable>.exe <input_file(s)> <output_csv>

Important:
- Most executables accept the output CSV file path as their last argument.
- For ecall_test: make sure your test/main_ecall_test.cpp supports the optional 3rd argument
  (output CSV). If not, it will always overwrite simulation_results/ecall_test.csv.

Atomic model experiments
------------------------

A1 — ECall (inside call forwarding)
    ./bin/ecall_test.exe input_data/ecall_inside.txt input_data/empty_outside.txt simulation_results/A1_ecall.csv

A2 — ECall (outside call forwarding)
    ./bin/ecall_test.exe input_data/empty_inside.txt input_data/ecall_outside.txt simulation_results/A2_ecall.csv

A3 — ECall (simultaneous inside/outside, inside priority)
    ./bin/ecall_test.exe input_data/ecall_inside.txt input_data/ecall_outside.txt simulation_results/A3_ecall.csv

A4 — EVehicle (delay / travel-time behavior)
    ./bin/evehicle_test.exe input_data/evehicle_single_in.txt simulation_results/A4_evehicle.csv

A5 — EControl (single request)
    ./bin/econtrol_test.exe input_data/econtrol_single_calls.txt input_data/econtrol_single_fback.txt simulation_results/A5_econtrol.csv

A6 — EControl (queued calls / FIFO)
    ./bin/econtrol_test.exe input_data/econtrol_queue_calls.txt input_data/econtrol_queue_fback.txt simulation_results/A6_econtrol.csv


Coupled + integration experiments
---------------------------------

C1 — ElevatorCoupled (sequential calls end-to-end)
    ./bin/elevator_test.exe input_data/elevator_calls_test.txt simulation_results/C1_elevator.csv

C2 — ElevatorCoupled (queue behavior / FIFO)
    ./bin/elevator_test.exe input_data/elevator_queue_calls.txt simulation_results/C2_elevator.csv

T1 — FreightElevatorTop (inside calls only)
    ./bin/freight_elevator_top.exe input_data/fe_inside_calls.txt input_data/empty_outside.txt simulation_results/T1_top.csv

T2 — FreightElevatorTop (inside priority at top input)
    ./bin/freight_elevator_top.exe input_data/fe_inside_calls.txt input_data/fe_outside_calls.txt simulation_results/T2_top.csv


4) Interpreting the CSV logs
----------------------------
Each CSV row contains:
- time
- model_id, model_name
- port_name (blank for state logs)
- data

5) Documentation files included at the repo root
--------------------------------------------------------------------------------
- FreightElevator.docx
- DEVSmodelForm_FreightElevator.docx