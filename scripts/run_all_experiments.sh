#!/usr/bin/env bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

"$SCRIPT_DIR/run_ecall.sh"
"$SCRIPT_DIR/run_evehicle.sh"
"$SCRIPT_DIR/run_econtrol.sh"
"$SCRIPT_DIR/run_elevator.sh"
"$SCRIPT_DIR/run_freight_elevator.sh"

echo "All documented experiments complete."
