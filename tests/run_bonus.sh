#!/usr/bin/env bash
set -u

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
BIN="${1:-$ROOT_DIR/cub3D_bonus}"
MAND="$ROOT_DIR/tests/mandatory"
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
	local out="$TMP_DIR/run.out"
	timeout 1s "$BIN" "$map_path" >"$out" 2>&1
	rc=$?
	if [ "$rc" -eq 124 ]; then
		pass "$name (running, timeout=124)"
	elif [ "$rc" -eq 1 ] && grep -q "mlx_init failed" "$out"; then
		pass "$name (parsed ok, headless mlx_init failed)"
	else
		fail "$name (exit=$rc expected=124)"
	fi
}

run_expect_running_timeout() {
	local name="$1"
	local duration="$2"
	local map_path="$3"
	local rc
	local out="$TMP_DIR/run.out"
	timeout "${duration}" "$BIN" "$map_path" >"$out" 2>&1
	rc=$?
	if [ "$rc" -eq 124 ]; then
		pass "$name (running, timeout=124)"
	elif [ "$rc" -eq 1 ] && grep -q "mlx_init failed" "$out"; then
		pass "$name (parsed ok, headless mlx_init failed)"
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
	if nm "$BIN" 2>/dev/null | grep -q "bonus_draw_minimap"; then
		pass "bonus symbol linked (bonus_draw_minimap)"
	else
		fail "bonus symbol missing (bonus_draw_minimap)"
	fi
	if nm "$BIN" 2>/dev/null | grep -q "bonus_door_try_toggle"; then
		pass "bonus symbol linked (bonus_door_try_toggle)"
	else
		fail "bonus symbol missing (bonus_door_try_toggle)"
	fi
else
	msg "SKIP: nm not found, symbol check skipped"
fi

run_expect_exit "bonus cli no argument" 1 "$BIN"
run_expect_exit "bonus parser missing file" 1 "$BIN" \
	"$MAND/parser/does_not_exist.cub"
run_expect_running "bonus retro small map" "$ROOT_DIR/tests/bonus/retro_small.cub"
run_expect_running "bonus retro maze map" "$ROOT_DIR/tests/bonus/retro_maze.cub"
run_expect_running "bonus retro wide map" "$ROOT_DIR/tests/bonus/retro_wide.cub"
run_expect_running "bonus retro tall map" "$ROOT_DIR/tests/bonus/retro_tall.cub"
run_expect_running "bonus retro corridor map" "$ROOT_DIR/tests/bonus/retro_corridor.cub"
run_expect_running "bonus retro tiles 2..9" "$ROOT_DIR/tests/bonus/retro_tiles_2_9.cub"
run_expect_exit "bonus parser invalid rgb" 1 "$BIN" \
	"$MAND/parser/bad_rgb.cub"
run_expect_exit "bonus parser bad texture extension" 1 "$BIN" \
	"$MAND/parser/bad_tex_extension.cub"
run_expect_exit "bonus parser unreadable texture path" 1 "$BIN" \
	"$MAND/parser/bad_tex_unreadable.cub"
run_expect_exit "bonus parser unreachable map" 1 "$BIN" \
	"$MAND/validation/unreachable.cub"
run_expect_exit "bonus init bad runtime texture NO" 1 "$BIN" \
	"$MAND/init/bad_texture_runtime.cub"
run_expect_exit "bonus init bad runtime texture EA" 1 "$BIN" \
	"$MAND/init/bad_texture_runtime_ea.cub"
run_expect_running "bonus render color extremes" \
	"$MAND/render/color_extremes.cub"

cat > "$ROOT_DIR/tests/.tmp_bonus/bonus_map_starts_with_wall.cub" <<MAP
NO $ROOT_DIR/textures/mandatory/no.xpm
SO $ROOT_DIR/textures/mandatory/so.xpm
WE $ROOT_DIR/textures/mandatory/we.xpm
EA $ROOT_DIR/textures/mandatory/ea.xpm
F 1,2,3
C 4,5,6

22222
2N002
22222
MAP
run_expect_running "bonus parser map starts with bonus wall" \
	"$ROOT_DIR/tests/.tmp_bonus/bonus_map_starts_with_wall.cub"

cat > "$ROOT_DIR/tests/.tmp_bonus/wrong_ext.txt" <<'MAP'
NO ../../textures/mandatory/no.xpm
SO ../../textures/mandatory/so.xpm
WE ../../textures/mandatory/we.xpm
EA ../../textures/mandatory/ea.xpm
F 1,2,3
C 4,5,6
111
1N1
111
MAP
run_expect_exit "bonus parser wrong extension runtime" 1 "$BIN" \
	"$ROOT_DIR/tests/.tmp_bonus/wrong_ext.txt"

cat > "$ROOT_DIR/tests/.tmp_bonus/irregular_bonus.cub" <<MAP
NO $ROOT_DIR/textures/mandatory/no.xpm
SO $ROOT_DIR/textures/mandatory/so.xpm
WE $ROOT_DIR/textures/mandatory/we.xpm
EA $ROOT_DIR/textures/mandatory/ea.xpm
F 20,30,40
C 60,70,80

111111
1N0001
11101
100001
111111
MAP
run_expect_running "bonus edge irregular lines" \
	"$ROOT_DIR/tests/.tmp_bonus/irregular_bonus.cub"

{
	cat <<MAP
NO $ROOT_DIR/textures/mandatory/no.xpm
SO $ROOT_DIR/textures/mandatory/so.xpm
WE $ROOT_DIR/textures/mandatory/we.xpm
EA $ROOT_DIR/textures/mandatory/ea.xpm
F 10,20,30
C 40,50,60

MAP
	python3 - <<'PY'
size = 80
print('1' * size)
for y in range(1, size - 1):
    if y == size // 2:
        print('1' + '0' * (size // 2 - 2) + 'N' + '0' * (size - (size // 2) - 2) + '1')
    else:
        print('1' + '0' * (size - 2) + '1')
print('1' * size)
PY
} > "$ROOT_DIR/tests/.tmp_bonus/large_bonus.cub"
run_expect_running_timeout "bonus edge large map" 2s \
	"$ROOT_DIR/tests/.tmp_bonus/large_bonus.cub"

msg "---"
msg "Bonus Total: pass=$PASS fail=$FAIL"

if [ "$FAIL" -ne 0 ]; then
	exit 1
fi
exit 0
