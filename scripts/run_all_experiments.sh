#!/usr/bin/env bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

bash "$SCRIPT_DIR/run_ecall.sh"
bash "$SCRIPT_DIR/run_evehicle.sh"
bash "$SCRIPT_DIR/run_econtrol.sh"
bash "$SCRIPT_DIR/run_elevator.sh"
bash "$SCRIPT_DIR/run_freight_elevator.sh"

echo "All documented experiments complete."
