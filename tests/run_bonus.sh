#!/usr/bin/env bash
set -u

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
BIN="${1:-$ROOT_DIR/cub3D}"
TMP_DIR="$ROOT_DIR/tests/.tmp_bonus"
PASS=0
FAIL=0

msg() { printf '%s\n' "$*"; }
pass() { PASS=$((PASS + 1)); msg "PASS: $*"; }
fail() { FAIL=$((FAIL + 1)); msg "FAIL: $*"; }

run_expect_exit() {
	local name="$1"
	local expected="$2"
	shift 2
	local rc
	"$@" >/dev/null 2>&1
	rc=$?
	if [ "$rc" -eq "$expected" ]; then
		pass "$name (exit=$rc)"
	else
		fail "$name (exit=$rc expected=$expected)"
	fi
}

run_expect_running() {
	local name="$1"
	local map_path="$2"
	local rc
	timeout 1s "$BIN" "$map_path" >/dev/null 2>&1
	rc=$?
	if [ "$rc" -eq 124 ]; then
		pass "$name (running, timeout=124)"
	else
		fail "$name (exit=$rc expected=124)"
	fi
}

mkdir -p "$TMP_DIR"
trap 'rm -rf "$TMP_DIR"' EXIT

if [ ! -x "$BIN" ]; then
	msg "Binary not found: $BIN"
	msg "Run: make bonus"
	exit 2
fi

if command -v nm >/dev/null 2>&1; then
	if nm "$BIN" 2>/dev/null | grep -q "retro_upscale_to_out"; then
		pass "bonus symbol linked (retro_upscale_to_out)"
	else
		fail "bonus symbol missing (retro_upscale_to_out)"
	fi
else
	msg "SKIP: nm not found, symbol check skipped"
fi

run_expect_exit "bonus cli no argument" 1 "$BIN"
run_expect_running "bonus retro small map" "$ROOT_DIR/tests/bonus/retro_small.cub"
run_expect_running "bonus retro maze map" "$ROOT_DIR/tests/bonus/retro_maze.cub"
run_expect_running "bonus retro wide map" "$ROOT_DIR/tests/bonus/retro_wide.cub"
run_expect_running "bonus retro tall map" "$ROOT_DIR/tests/bonus/retro_tall.cub"
run_expect_running "bonus retro corridor map" "$ROOT_DIR/tests/bonus/retro_corridor.cub"
run_expect_exit "bonus parser invalid rgb" 1 "$BIN" \
	"$ROOT_DIR/tests/parser/bad_rgb.cub"
run_expect_exit "bonus parser unreachable map" 1 "$BIN" \
	"$ROOT_DIR/tests/validation/unreachable.cub"

cat > "$ROOT_DIR/tests/.tmp_bonus/wrong_ext.txt" <<'MAP'
NO ../../textures/no.xpm
SO ../../textures/so.xpm
WE ../../textures/we.xpm
EA ../../textures/ea.xpm
F 1,2,3
C 4,5,6
111
1N1
111
MAP
run_expect_exit "bonus parser wrong extension runtime" 1 "$BIN" \
	"$ROOT_DIR/tests/.tmp_bonus/wrong_ext.txt"

msg "---"
msg "Bonus Total: pass=$PASS fail=$FAIL"

if [ "$FAIL" -ne 0 ]; then
	exit 1
fi
exit 0
