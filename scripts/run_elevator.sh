#!/usr/bin/env bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
cd "$REPO_ROOT"

mkdir -p simulation_results

make clean
make

./bin/ELEVATOR_TEST > simulation_results/elevator_output.txt

echo "Elevator coupled test complete."
echo "CAT results in simulation_results/elevator_output.txt"
