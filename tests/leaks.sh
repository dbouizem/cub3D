#!/usr/bin/env bash
set -u

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
MAND_BIN="$ROOT_DIR/cub3D"
BONUS_BIN="$ROOT_DIR/cub3D_bonus"
LOG_DIR="$ROOT_DIR/tests/valgrind_logs"
PASS=0
FAIL=0
TOTAL=0

msg() { printf '%s\n' "$*"; }

check_binary() {
	local bin="$1"
	local target="$2"

	if [ ! -x "$bin" ]; then
		msg "Missing binary: $bin"
		msg "Run: make $target"
		exit 2
	fi
}

run_map() {
	local mode="$1"
	local bin="$2"
	local map="$3"
	local rel
	local log
	local rc

	TOTAL=$((TOTAL + 1))
	rel="${map#$ROOT_DIR/}"
	log="$LOG_DIR/${mode}_$(echo "$rel" | tr '/.' '__').log"
	valgrind --leak-check=full --show-leak-kinds=all \
		--errors-for-leak-kinds=definite,indirect,possible \
		--error-exitcode=99 --track-fds=yes --track-origins=yes \
		"$bin" "$map" >"$log" 2>&1
	rc=$?
	if [ "$rc" -eq 99 ] \
		|| grep -q "ERROR SUMMARY: [1-9]" "$log" \
		|| grep -Eq "definitely lost: [1-9]|indirectly lost: [1-9]|possibly lost: [1-9]" "$log"; then
		FAIL=$((FAIL + 1))
		msg "FAIL [$mode] $rel"
		msg "  log: $log"
		grep -E "Invalid read|Invalid write|uninitialised|definitely lost|indirectly lost|possibly lost|ERROR SUMMARY" "$log" | head -n 12
	else
		PASS=$((PASS + 1))
		msg "PASS [$mode] $rel"
	fi
}

mkdir -p "$LOG_DIR"
check_binary "$MAND_BIN" ""
check_binary "$BONUS_BIN" "bonus"

while IFS= read -r map; do
	run_map "mandatory" "$MAND_BIN" "$map"
done < <(find "$ROOT_DIR/tests/mandatory" -type f -name "*.cub" | sort)

while IFS= read -r map; do
	run_map "bonus" "$BONUS_BIN" "$map"
done < <(find "$ROOT_DIR/tests/bonus" -type f -name "*.cub" | sort)

msg "---"
msg "Leak tests: total=$TOTAL pass=$PASS fail=$FAIL"
msg "Logs: $LOG_DIR"

if [ "$FAIL" -ne 0 ]; then
	exit 1
fi
exit 0
