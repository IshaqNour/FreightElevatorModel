#!/usr/bin/env bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
cd "$REPO_ROOT"

mkdir -p simulation_results

make clean
make

./bin/ECALL_TEST > simulation_results/ecall_output.txt

echo "ECall test complete."
echo "CAT results in simulation_results/ecall_output.txt"
