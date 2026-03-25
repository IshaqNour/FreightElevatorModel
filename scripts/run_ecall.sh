#!/usr/bin/env bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
cd "$REPO_ROOT"

mkdir -p simulation_results

make clean
make

./bin/ECALL_TEST input_data/ecall_inside.txt input_data/empty_outside.txt simulation_results/A1_ecall.csv
./bin/ECALL_TEST input_data/empty_inside.txt input_data/ecall_outside.txt simulation_results/A2_ecall.csv
./bin/ECALL_TEST input_data/ecall_inside.txt input_data/ecall_outside.txt simulation_results/A3_ecall.csv

echo "ECall experiments complete."
echo "Generated:"
echo "  simulation_results/A1_ecall.csv"
echo "  simulation_results/A2_ecall.csv"
echo "  simulation_results/A3_ecall.csv"
