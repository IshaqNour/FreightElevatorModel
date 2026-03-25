#!/usr/bin/env bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
cd "$REPO_ROOT"

mkdir -p simulation_results

make clean
make

./bin/ECONTROL_TEST input_data/econtrol_single_calls.txt input_data/econtrol_single_fback.txt simulation_results/A5_econtrol.csv
./bin/ECONTROL_TEST input_data/econtrol_queue_calls.txt input_data/econtrol_queue_fback.txt simulation_results/A6_econtrol.csv

echo "EControl experiments complete."
echo "Generated:"
echo "  simulation_results/A5_econtrol.csv"
echo "  simulation_results/A6_econtrol.csv"
