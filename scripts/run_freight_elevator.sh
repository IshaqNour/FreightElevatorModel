#!/usr/bin/env bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
cd "$REPO_ROOT"

mkdir -p simulation_results

make clean
make

./bin/FREIGHT_ELEVATOR_TEST input_data/fe_inside_calls.txt input_data/empty_outside.txt simulation_results/T1_top.csv
./bin/FREIGHT_ELEVATOR_TEST input_data/fe_inside_calls.txt input_data/fe_outside_calls.txt simulation_results/T2_top.csv

echo "Top-level experiments complete."
echo "Generated:"
echo "  simulation_results/T1_top.csv"
echo "  simulation_results/T2_top.csv"
