#!/usr/bin/env bash
set -u

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
BIN="${1:-$ROOT_DIR/cub3D}"
MAND="$ROOT_DIR/tests/mandatory"
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

mkdir -p "$TMP_DIR"
trap 'rm -rf "$TMP_DIR"' EXIT

if [ ! -x "$BIN" ]; then
  msg "Binary not found: $BIN"
  msg "Run: make"
  exit 2
fi

# Issue 1: CLI / file opening.
run_expect_exit "cli no argument" 1 "$BIN"
run_expect_exit "parser missing file" 1 "$BIN" "$MAND/parser/does_not_exist.cub"

# Existing parser/validation suite.
run_expect_exit "parser bad_rgb" 1 "$BIN" "$MAND/parser/bad_rgb.cub"
run_expect_exit "parser missing_header" 1 "$BIN" "$MAND/parser/missing_header.cub"
run_expect_running "parser ok" "$MAND/parser/ok.cub"
run_expect_running "parser ok_o" "$MAND/parser/ok_o.cub"
run_expect_running "parser order and empty lines ok" \
  "$MAND/parser/order_empty_ok.cub"
run_expect_running "parser ok tabs/spaces" \
  "$MAND/parser/ok_tabs_spaces.cub"
run_expect_exit "parser duplicate NO" 1 "$BIN" "$MAND/parser/dup_no.cub"
run_expect_exit "parser duplicate F" 1 "$BIN" "$MAND/parser/dup_f.cub"
run_expect_exit "parser duplicate C" 1 "$BIN" "$MAND/parser/dup_c.cub"
run_expect_exit "parser missing NO" 1 "$BIN" "$MAND/parser/missing_no.cub"
run_expect_exit "parser missing SO" 1 "$BIN" "$MAND/parser/missing_so.cub"
run_expect_exit "parser missing WE" 1 "$BIN" "$MAND/parser/missing_we.cub"
run_expect_exit "parser missing C" 1 "$BIN" "$MAND/parser/missing_c.cub"
run_expect_exit "parser missing EA" 1 "$BIN" "$MAND/parser/missing_ea.cub"
run_expect_exit "parser bad rgb missing component" 1 "$BIN" \
  "$MAND/parser/bad_rgb_missing_component.cub"
run_expect_exit "parser bad rgb chars" 1 "$BIN" \
  "$MAND/parser/bad_rgb_chars.cub"
run_expect_exit "parser bad rgb trailing" 1 "$BIN" \
  "$MAND/parser/bad_rgb_trailing.cub"
run_expect_exit "parser bad texture extension" 1 "$BIN" \
  "$MAND/parser/bad_tex_extension.cub"
run_expect_exit "parser unreadable texture path" 1 "$BIN" \
  "$MAND/parser/bad_tex_unreadable.cub"
run_expect_exit "parser unknown identifier" 1 "$BIN" \
  "$MAND/parser/unknown_identifier.cub"

run_expect_running "validation good" "$MAND/validation/good.cub"
run_expect_running "validation good shifted spaces" \
  "$MAND/validation/good_shifted_spaces.cub"
run_expect_running "validation good trailing spaces" \
  "$MAND/validation/good_trailing_spaces.cub"
run_expect_running "validation good player E" \
  "$MAND/validation/good_player_e.cub"
run_expect_running "validation good player S" \
  "$MAND/validation/good_player_s.cub"
run_expect_running "validation good player W" \
  "$MAND/validation/good_player_w.cub"
run_expect_exit "validation invalid_chars" 1 "$BIN" "$MAND/validation/invalid_chars.cub"
run_expect_exit "validation tab in map" 1 "$BIN" "$MAND/validation/tab_in_map.cub"
run_expect_exit "validation multi_player" 1 "$BIN" "$MAND/validation/multi_player.cub"
run_expect_exit "validation no_player" 1 "$BIN" "$MAND/validation/no_player.cub"
run_expect_exit "validation open_top" 1 "$BIN" "$MAND/validation/open_top.cub"
run_expect_exit "validation open_bottom" 1 "$BIN" "$MAND/validation/open_bottom.cub"
run_expect_exit "validation open_left" 1 "$BIN" "$MAND/validation/open_left.cub"
run_expect_exit "validation open_right" 1 "$BIN" "$MAND/validation/open_right.cub"
run_expect_exit "validation open_irregular" 1 "$BIN" "$MAND/validation/open_irregular.cub"
run_expect_exit "validation empty line inside map" 1 "$BIN" \
  "$MAND/validation/empty_line_inside_map.cub"
run_expect_exit "validation trailing garbage after map" 1 "$BIN" \
  "$MAND/validation/trailing_garbage_after_map.cub"
run_expect_exit "validation unreachable" 1 "$BIN" "$MAND/validation/unreachable.cub"
run_expect_exit "validation open internal space" 1 "$BIN" \
  "$MAND/validation/open_internal_space.cub"
run_expect_exit "validation open missing short row" 1 "$BIN" \
  "$MAND/validation/open_missing_short_row.cub"

# Mandatory must reject bonus-only map symbols.
run_expect_exit "validation rejects bonus door char" 1 "$BIN" \
  "$MAND/edge/bonus_door_char.cub"

run_expect_exit "validation rejects bonus sprite char" 1 "$BIN" \
  "$MAND/edge/bonus_sprite_char.cub"

# Issue 3: init / mlx / texture loading / color bounds.
run_expect_running "init color bounds 0/255" \
  "$MAND/init/ok_color_bounds.cub"
run_expect_exit "init bad runtime texture NO" 1 "$BIN" \
  "$MAND/init/bad_texture_runtime.cub"
run_expect_exit "init bad runtime texture EA" 1 "$BIN" \
  "$MAND/init/bad_texture_runtime_ea.cub"

# Issue 6: final render integration (textures + floor/ceiling).
run_expect_running "render box N orientation" "$MAND/render/box_n.cub"
run_expect_running "render box E orientation" "$MAND/render/box_e.cub"
run_expect_running "render box S orientation" "$MAND/render/box_s.cub"
run_expect_running "render box W orientation" "$MAND/render/box_w.cub"
run_expect_running "render floor/ceiling color extremes" \
  "$MAND/render/color_extremes.cub"

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
run_expect_running "edge irregular lines" "$MAND/edge/irregular_ok.cub"

msg "---"
msg "Total: pass=$PASS fail=$FAIL"

if [ "$FAIL" -ne 0 ]; then
  exit 1
fi
exit 0
