#!/usr/bin/env bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
cd "$REPO_ROOT"

mkdir -p simulation_results

make clean
make

./bin/ELEVATOR_TEST input_data/elevator_calls_test.txt simulation_results/C1_elevator.csv
./bin/ELEVATOR_TEST input_data/elevator_queue_calls.txt simulation_results/C2_elevator.csv

echo "Elevator coupled experiments complete."
echo "Generated:"
echo "  simulation_results/C1_elevator.csv"
echo "  simulation_results/C2_elevator.csv"
