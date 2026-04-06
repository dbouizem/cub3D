#!/usr/bin/env bash
set -u

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
BIN="${1:-$ROOT_DIR/cub3D}"
TMP_DIR="$ROOT_DIR/tests/.tmp"
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
  msg "Run: make"
  exit 2
fi

# Issue 1: CLI / file opening.
run_expect_exit "cli no argument" 1 "$BIN"
run_expect_exit "parser missing file" 1 "$BIN" "$ROOT_DIR/tests/parser/does_not_exist.cub"

# Existing parser/validation suite.
run_expect_exit "parser bad_rgb" 1 "$BIN" "$ROOT_DIR/tests/parser/bad_rgb.cub"
run_expect_exit "parser missing_header" 1 "$BIN" "$ROOT_DIR/tests/parser/missing_header.cub"
run_expect_running "parser ok" "$ROOT_DIR/tests/parser/ok.cub"
run_expect_running "parser ok_o" "$ROOT_DIR/tests/parser/ok_o.cub"
run_expect_running "parser order and empty lines ok" \
  "$ROOT_DIR/tests/parser/order_empty_ok.cub"
run_expect_running "parser ok tabs/spaces" \
  "$ROOT_DIR/tests/parser/ok_tabs_spaces.cub"
run_expect_exit "parser duplicate NO" 1 "$BIN" "$ROOT_DIR/tests/parser/dup_no.cub"
run_expect_exit "parser duplicate F" 1 "$BIN" "$ROOT_DIR/tests/parser/dup_f.cub"
run_expect_exit "parser missing C" 1 "$BIN" "$ROOT_DIR/tests/parser/missing_c.cub"
run_expect_exit "parser missing EA" 1 "$BIN" "$ROOT_DIR/tests/parser/missing_ea.cub"
run_expect_exit "parser bad rgb missing component" 1 "$BIN" \
  "$ROOT_DIR/tests/parser/bad_rgb_missing_component.cub"
run_expect_exit "parser bad rgb chars" 1 "$BIN" \
  "$ROOT_DIR/tests/parser/bad_rgb_chars.cub"
run_expect_exit "parser bad rgb trailing" 1 "$BIN" \
  "$ROOT_DIR/tests/parser/bad_rgb_trailing.cub"
run_expect_exit "parser bad texture extension" 1 "$BIN" \
  "$ROOT_DIR/tests/parser/bad_tex_extension.cub"
run_expect_exit "parser unreadable texture path" 1 "$BIN" \
  "$ROOT_DIR/tests/parser/bad_tex_unreadable.cub"
run_expect_exit "parser unknown identifier" 1 "$BIN" \
  "$ROOT_DIR/tests/parser/unknown_identifier.cub"

run_expect_running "validation good" "$ROOT_DIR/tests/validation/good.cub"
run_expect_running "validation good shifted spaces" \
  "$ROOT_DIR/tests/validation/good_shifted_spaces.cub"
run_expect_running "validation good player E" \
  "$ROOT_DIR/tests/validation/good_player_e.cub"
run_expect_running "validation good player S" \
  "$ROOT_DIR/tests/validation/good_player_s.cub"
run_expect_running "validation good player W" \
  "$ROOT_DIR/tests/validation/good_player_w.cub"
run_expect_exit "validation invalid_chars" 1 "$BIN" "$ROOT_DIR/tests/validation/invalid_chars.cub"
run_expect_exit "validation tab in map" 1 "$BIN" "$ROOT_DIR/tests/validation/tab_in_map.cub"
run_expect_exit "validation multi_player" 1 "$BIN" "$ROOT_DIR/tests/validation/multi_player.cub"
run_expect_exit "validation no_player" 1 "$BIN" "$ROOT_DIR/tests/validation/no_player.cub"
run_expect_exit "validation open_top" 1 "$BIN" "$ROOT_DIR/tests/validation/open_top.cub"
run_expect_exit "validation open_bottom" 1 "$BIN" "$ROOT_DIR/tests/validation/open_bottom.cub"
run_expect_exit "validation open_left" 1 "$BIN" "$ROOT_DIR/tests/validation/open_left.cub"
run_expect_exit "validation open_right" 1 "$BIN" "$ROOT_DIR/tests/validation/open_right.cub"
run_expect_exit "validation open_irregular" 1 "$BIN" "$ROOT_DIR/tests/validation/open_irregular.cub"
run_expect_exit "validation empty line inside map" 1 "$BIN" \
  "$ROOT_DIR/tests/validation/empty_line_inside_map.cub"
run_expect_exit "validation trailing garbage after map" 1 "$BIN" \
  "$ROOT_DIR/tests/validation/trailing_garbage_after_map.cub"
run_expect_exit "validation unreachable" 1 "$BIN" "$ROOT_DIR/tests/validation/unreachable.cub"
run_expect_exit "validation open internal space" 1 "$BIN" \
  "$ROOT_DIR/tests/validation/open_internal_space.cub"

# Issue 3: init / mlx / texture loading / color bounds.
run_expect_running "init color bounds 0/255" \
  "$ROOT_DIR/tests/init/ok_color_bounds.cub"
run_expect_exit "init bad runtime texture NO" 1 "$BIN" \
  "$ROOT_DIR/tests/init/bad_texture_runtime.cub"
run_expect_exit "init bad runtime texture EA" 1 "$BIN" \
  "$ROOT_DIR/tests/init/bad_texture_runtime_ea.cub"

# Issue 6: final render integration (textures + floor/ceiling).
run_expect_running "render box N orientation" "$ROOT_DIR/tests/render/box_n.cub"
run_expect_running "render box E orientation" "$ROOT_DIR/tests/render/box_e.cub"
run_expect_running "render box S orientation" "$ROOT_DIR/tests/render/box_s.cub"
run_expect_running "render box W orientation" "$ROOT_DIR/tests/render/box_w.cub"
run_expect_running "render floor/ceiling color extremes" \
  "$ROOT_DIR/tests/render/color_extremes.cub"

# Edge: wrong extension.
cat > "$TMP_DIR/wrong_ext.txt" <<'MAP'
NO /tmp/no.xpm
SO /tmp/so.xpm
WE /tmp/we.xpm
EA /tmp/ea.xpm
F 1,2,3
C 4,5,6
111
1N1
111
MAP
run_expect_exit "edge wrong extension" 1 "$BIN" "$TMP_DIR/wrong_ext.txt"

# Edge: irregular lines (still enclosed, should run).
cat > "$TMP_DIR/irregular_open.cub" <<MAP
NO $ROOT_DIR/textures/no.xpm
SO $ROOT_DIR/textures/so.xpm
WE $ROOT_DIR/textures/we.xpm
EA $ROOT_DIR/textures/ea.xpm
F 1,2,3
C 4,5,6

111111
1N0001
11101
100001
111111
MAP
run_expect_running "edge irregular lines" "$TMP_DIR/irregular_open.cub"

# Perf-ish: large enclosed map should still run.
{
  cat <<MAP
NO $ROOT_DIR/textures/no.xpm
SO $ROOT_DIR/textures/so.xpm
WE $ROOT_DIR/textures/we.xpm
EA $ROOT_DIR/textures/ea.xpm
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
} > "$TMP_DIR/large_ok.cub"
run_expect_running "edge large map" "$TMP_DIR/large_ok.cub"

msg "---"
msg "Total: pass=$PASS fail=$FAIL"

if [ "$FAIL" -ne 0 ]; then
  exit 1
fi
exit 0
