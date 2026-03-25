#!/usr/bin/env bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
cd "$REPO_ROOT"

mkdir -p simulation_results

make clean
make

./bin/EVEHICLE_TEST input_data/evehicle_single_in.txt simulation_results/A4_evehicle.csv

echo "EVehicle experiment complete."
echo "Generated:"
echo "  simulation_results/A4_evehicle.csv"
