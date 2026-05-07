*This project has been created as part of the 42 curriculum by brrr1, dbouizem.*

# cub3D

## Description

`cub3D` is a raycasting project inspired by Wolfenstein 3D.
The goal is to render a first-person 3D view from a 2D `.cub` map using
MiniLibX, with:

- directional wall textures (`NO`, `SO`, `WE`, `EA`),
- floor and ceiling colors (`F`, `C`),
- player movement and camera rotation,
- strict map parsing and validation.

The repository is split between mandatory code in `srcs/` and bonus-only code
in `srcs_bonus/`. Mandatory mode stays isolated through no-op bonus API files,
while `make bonus` links the real bonus systems.

## Documentation

Project documentation is available here:
[cub3D documentation](https://cub3d.djihane-bouizem.workers.dev/en/).

## Features

- Mandatory raycasting renderer with one texture per wall direction.
- `.cub` parser with strict identifier, RGB, texture path, and map validation.
- Player spawn parsing for `N`, `S`, `E`, and `W` orientations.
- Smooth movement using frame delta time.
- Wall collision in mandatory mode.
- Window cleanup through `ESC` and the window close button.
- Bonus mode with retro rendering, minimap, doors, pickups, animated sprites,
  weapon/HUD overlay, multiple bonus wall sets, and level switching.

## Instructions

### Requirements

- Linux (X11)
- `cc`
- `make`

### Build

```bash
make
make bonus
```

### Run

```bash
./cub3D maps/mandatory/map.cub
./cub3D maps/mandatory/maze.cub
./cub3D tests/mandatory/validation/good.cub
./cub3D tests/mandatory/render/box_n.cub
./cub3D_bonus tests/bonus/retro_small.cub
./cub3D_bonus maps/bonus/level1.cub
./cub3D_bonus maps/bonus/all_maps.cub
```

The `maps/` directory contains playable maps. The `tests/` directory contains
small correction-oriented maps for parser, validation, initialization, and
render checks.

### Controls

| Key | Use |
| --- | --- |
| `ESC` | Close the program |
| `W` / `Z` | Move forward |
| `S` | Move backward |
| `A` / `Q` | Strafe left |
| `D` | Strafe right |
| `Left Arrow` | Rotate left |
| `Right Arrow` | Rotate right |
| Red cross | Quit cleanly |

### Bonus Controls

| Key | Use |
| --- | --- |
| Mouse move | Mouse look |
| Mouse wheel | Minimap zoom |
| `E` | Interact with bonus doors |
| `Space` | Fire weapon in bonus mode |
| `F1`, `F2`, `F3` | Resolution presets |
| `F4` | Load next bonus level |

### Useful Commands

```bash
make test
make test_bonus
norminette srcs include
norminette srcs include libft
norminette srcs include libft srcs_bonus
valgrind --track-origins=yes --leak-check=full --track-fds=yes ./cub3D maps/mandatory/map.cub
```

## Verification

Use these checks before evaluation:

```bash
norminette include srcs srcs_bonus
make
make bonus
make test
make test_bonus
```

If `make test_bonus` fails with `mlx_init failed`, the environment probably has
no X11 display. Parser-only failures are still meaningful; runtime smoke tests
need a graphical session.

The test scripts also accept `mlx_init failed` as a successful parse/init path
when they run in a headless environment, so they remain useful on machines
without an X11 display.

For MiniLibX/X11 runs, Valgrind may report an uninitialized byte inside
`mlx_int_anti_resize_win` during `mlx_new_window`. The leak result to check is
the heap summary. A clean run should end with `All heap blocks were freed`.

## Project Organization

| Issue | Owner | Related Phases | Branch |
|------|------------|-------------|--------|
| Issue 1 - `.cub` file reading and config parsing | A + B | Phase 0: Architecture<br>Phase 1: Setup<br>Phase 2: Config parsing | `1-parsing-cub-file` |
| Issue 2 - Full map extraction and validation | B | Phase 3: Map validation | `2-map-validation` |
| Issue 3 - Game and MiniLibX initialization | A | Phase 4: MLX + Textures | `3-mlx-init` |
| Issue 4 - Player system and input handling | B | Phase 5: Player system | `4-player-inputs` |
| Issue 5 - Ray-casting implementation | A | Phase 6: Raycasting | `5-raycasting` |
| Issue 6 - Final rendering with textures, floor, and ceiling | B | Phase 7: Textured render | `6-textured-render` |
| Issue 7 - Errors, cleanup, tests, and polishing | A + B | Phase 8: Polish | `7-polish` |

## Project Layout

- `srcs/`
  Mandatory gameplay, parsing, raycasting, rendering, hooks, and shared core
  logic.
- `srcs_bonus/`
  Bonus-only systems. Mandatory mode stays isolated through the no-op files in
  `srcs_bonus/noop/`.
- `include/`
  Shared headers plus bonus constants, structs, and prototypes.
- `tests/`
  Parser and project-level validation helpers.
- `maps/`
  Playable mandatory and bonus `.cub` maps.
- `textures/`
  Mandatory and bonus XPM texture assets.
- `docs/`
  Project documentation.
- `libft/`
  Authorized libft implementation used by the project.
- `minilibx/`
  MiniLibX sources used to build the graphical program.

## Mandatory Scene Format

The program expects exactly one argument: a file ending in `.cub`.

Mandatory identifiers can appear in any order before the map:

```text
NO ./textures/mandatory/no.xpm
SO ./textures/mandatory/so.xpm
WE ./textures/mandatory/we.xpm
EA ./textures/mandatory/ea.xpm
F 30,30,30
C 180,180,220
111111
100001
10N001
111111
```

Mandatory configuration rules:

- `NO`, `SO`, `WE`, and `EA` define readable `.xpm` wall textures.
- `F` and `C` define floor and ceiling RGB colors in the `[0,255]` range.
- the map must be the last block in the file.
- the map accepts `0`, `1`, spaces, and one player start among `N`, `S`, `E`,
  and `W`.
- spaces are part of the map and are validated as void outside playable cells.
- the map must be closed by walls.
- any invalid identifier, duplicate key, invalid RGB value, invalid texture
  path, missing player, multiple players, open map, or trailing garbage causes
  `Error` followed by an explicit message.

## Test Suite

The mandatory test suite is grouped by correction topic:

- `tests/mandatory/parser/`
  header order, missing keys, duplicate keys, RGB parsing, unknown identifiers,
  and texture path errors.
- `tests/mandatory/validation/`
  player count, invalid map characters, open maps, spaces, irregular maps, and
  trailing garbage after the map.
- `tests/mandatory/init/`
  runtime texture loading and RGB boundary checks.
- `tests/mandatory/render/`
  orientation maps and floor/ceiling color checks.
- `tests/mandatory/edge/`
  mandatory rejection of bonus-only map symbols.
- `tests/bonus/`
  bonus smoke maps for retro dimensions and bonus wall tiles.

## Bonus Notes

The bonus build now uses:

- a dedicated retro render pipeline,
- a grouped bonus context inside `t_app`,
- a modular minimap renderer,
- bonus door state/query helpers,
- a separate bonus smoke-test suite.

The previous `srcs_bonus/README.md` architecture overview has been merged into
the sections below so the project keeps a single root README.

## Bonus Architecture

This section is the single reference for project structure, runtime flow, and
bonus-mode conventions that are easy to forget during correction or future
refactors.

The bonus build uses:

- a dedicated retro render pipeline,
- a grouped bonus context inside `t_app`,
- a modular minimap renderer,
- bonus door state/query helpers,
- a separate bonus smoke-test suite.

### Bonus Directory Map

- `retro/`
  Bonus render target helpers, minimap, bonus wall rules, wall texture loading,
  animated wall selection, and shading.
- `hud/`
  Face state, pistol overlay, status bar, text/glyph drawing, HUD panels, and
  screen-space blitting helpers.
- `sprites/`
  Runtime sprite storage, capacity management, sprite sorting, projection,
  visible bounds, shadow drawing, texture loading, and render entrypoint.
- `pickups/`
  Pickup discovery from the map, active pickup updates, stat effects, and
  conversion from active pickups to renderable sprites.
- `doors/`
  Door discovery, state updates, collision/blocking queries, and interaction
  helpers.
- `levels/`
  Bonus level list, current path lookup, next-level reload, texture transfer,
  and cleanup helpers.
- `noop/`
  Mandatory-build fallbacks for bonus APIs. These files keep mandatory sources
  independent from bonus internals while still allowing shared calls.

### Key Bonus Integration Files

- `include/defines_bonus.h`
  All bonus constants: map alphabets, wall/door texture paths, minimap values,
  shading values, pickup stats, weapon timing, and HUD settings.
- `include/structs_bonus.h`
  Bonus runtime state grouped under `app->bonus`.
- `include/cub3d_bonus.h`
  Bonus function prototypes grouped by subsystem.
- `Makefile`
  `BONUS_SRCS` lists real bonus modules. `BONUS_NOOP_SRCS` lists mandatory
  fallbacks, and `BONUS_REPLACE_SRCS` removes those fallbacks for `make bonus`.

### Runtime Flow

```text
draw_frame()
  -> update frame timing and input
  -> update doors, HUD state, pickups
  -> retro_begin()
  -> draw background
  -> raycast_scene()
  -> bonus_draw_sprites()
  -> bonus_draw_minimap()
  -> apply_world_vignette()
  -> retro_render()
  -> bonus_draw_hud()
  -> mlx_put_image_to_window()
```

The current bonus renderer draws the world directly into the bonus output image.
`retro_begin()` swaps `app->frame` to that output image, `retro_render()`
restores the normal frame pointer, and the HUD is drawn last so it stays sharp
and readable. The old upscale helper is still present for reference, but it is
not part of the normal per-frame path.

### Full Keycode Reference

The project uses Linux/X11 MLX keycodes from `include/defines.h`.

| Key | Macro | Use |
| --- | --- | --- |
| `ESC` | `KEY_ESC` | Close the program |
| `W` / `Z` | `KEY_W`, `KEY_Z` | Move forward |
| `S` | `KEY_S` | Move backward |
| `A` / `Q` | `KEY_A`, `KEY_Q` | Strafe left |
| `D` | `KEY_D` | Strafe right |
| `Left` | `KEY_LEFT` | Rotate left |
| `Right` | `KEY_RIGHT` | Rotate right |
| `E` | `KEY_E` | Interact with a door |
| `Space` | `KEY_SPACE` | Fire weapon in bonus mode |
| `F1`, `F2`, `F3` | `KEY_F1`, `KEY_F2`, `KEY_F3` | Resolution presets |
| `F4` | `KEY_F4` | Load next bonus level |
| Mouse move | `EVENT_MOUSEMOVE` | Mouse look |
| Scroll up/down | `BUTTON_SCROLL_UP`, `BUTTON_SCROLL_DOWN` | Minimap zoom |

## Map Characters

Mandatory parsing supports the subject map characters:

| Character | Meaning |
| --- | --- |
| `0` | Empty floor |
| `1` | Mandatory wall |
| space | Void outside the map |
| `N`, `S`, `E`, `W` | Player start and orientation |

Bonus mode extends the map alphabet with constants from
`include/defines_bonus.h`:

| Constant | Characters | Meaning |
| --- | --- | --- |
| `BONUS_DOOR_SET` | `AD` | Door-capable bonus tiles |
| `BONUS_PLAYER_SET` | `NSEW` | Player start and orientation |
| `BONUS_WALL_SYMBOL_SET` | punctuation symbols | Bonus symbol wall tiles |
| `BONUS_SPRITE_SET` | `*@)/` | Bonus sprites and pickups |

Numeric bonus wall tiles are `2` to `9`.

Player detection still uses only `N`, `S`, `E`, and `W` through
`is_open_cell()` and `find_player()`. Bonus mode does not add extra player
spawn letters beyond the mandatory orientations.

## Door Tiles

Door characters are listed in `BONUS_DOOR_SET`. Door state is not stored only
in the map grid; it is tracked in `app->bonus.doors` so doors can animate and
change collision state over time.

Door texture mapping:

| Door tile | Texture |
| --- | --- |
| `A` | `BONUS_DOOR_A_XPM` |
| all other supported door letters | `BONUS_DOOR_DEFAULT_XPM` fallback |

The door systems live in `srcs_bonus/doors/`.

## Sprite And Pickup Tiles

Sprite characters are listed in `BONUS_SPRITE_SET`.

| Character | Role |
| --- | --- |
| `*` | Health pickup |
| `@` | Ammo pickup |
| `)` | Armor pickup |
| `/` | Animated score pickup |

Pickup data is discovered and managed in `srcs_bonus/pickups/`. Renderable
sprite arrays and sprite drawing live in `srcs_bonus/sprites/`.

## Animated Walls

Animated wall tiles are grouped by tile character.

| Tile | Frames | Texture macros |
| --- | --- | --- |
| `o` | 3 | `BONUS_WALL_O1_XPM`, `BONUS_WALL_O2_XPM`, `BONUS_WALL_O3_XPM` |
| `p` | 3 | `BONUS_WALL_P1_XPM`, `BONUS_WALL_P2_XPM`, `BONUS_WALL_P3_XPM` |
| `q` | 3 | `BONUS_WALL_Q1_XPM`, `BONUS_WALL_Q2_XPM`, `BONUS_WALL_Q3_XPM` |
| `*` | 4 | `BONUS_WALL_STAR1_XPM` to `BONUS_WALL_STAR4_XPM` |
| `.` | 4 | `BONUS_WALL_DOT1_XPM` to `BONUS_WALL_DOT4_XPM` |
| `(` | 4 | `BONUS_WALL_LPAREN1_XPM` to `BONUS_WALL_LPAREN4_XPM` |

Animation timing is configured by the matching `BONUS_ANIM_*_FPS` macros.
Loading is handled in `srcs_bonus/retro/walls_anim_io.c`, and picking the frame
for rendering is handled in `srcs_bonus/retro/walls_anim_pick.c`.

## Static Wall Texture Mapping

Static wall texture paths are grouped by level set in `defines_bonus.h`.

| Group | Tiles | Texture family |
| --- | --- | --- |
| Level 1 stone | `2` to `7` | `textures/bonus/walls/wall_s/` |
| Level 2 area | `g` to `n` | `textures/bonus/walls/wall_a/` |
| Level 3 gray symbols | `!`, `"`, `#`, `$`, `%`, `&` | `textures/bonus/walls/wall_g/` |
| Level 4 tech | `d`, `e`, `f` | `textures/bonus/walls/wall_t/` |
| Level 5 computer | `+`, comma, `-` | `textures/bonus/walls/wall_c/` |
| Level 6 marble | `r` to `z` | `textures/bonus/walls/wall_m/` |
| Level 7 flesh | `'` | `textures/bonus/walls/wall_f/` |
| Level 8 exit | `8`, `9`, `a`, `b`, `c` | `textures/bonus/walls/wall_e/` |
| Fallback symbols | other accepted punctuation | `BONUS_WALL_DEFAULT_XPM` |

Wall path table initialization is in `srcs_bonus/retro/walls_paths.c`.
Texture loading is in `srcs_bonus/retro/walls_io.c` and
`srcs_bonus/retro/walls_symbol_io.c`.

## Adding A New Bonus Tile

When adding a new bonus map tile, update the project in this order:

1. Add or update the character set in `include/defines_bonus.h`.
2. Add texture macros in `include/defines_bonus.h`.
3. Update the relevant path table in `srcs_bonus/retro/walls_paths.c` or
   symbol loading in `srcs_bonus/retro/walls_symbol_io.c`.
4. Update solid/valid rules in `srcs_bonus/retro/walls_rules.c`.
5. Update pickers under `srcs_bonus/retro/` if the tile is animated or special.
6. Add a parser/validation test map if the tile changes map validity.

Keep the mandatory build isolated: if mandatory code needs to call a bonus API,
there must be a no-op fallback under `srcs_bonus/noop/`.

## Development Rules

- Keep mandatory behavior independent from bonus internals.
- Add new bonus logic under `srcs_bonus/<feature>/`.
- Do not add `_bonus.c` files inside `srcs/`.
- Keep shared bonus state inside `app->bonus`.
- Prefer small files grouped by responsibility over large files split only by
  norminette pressure.
- Avoid global variables. Use local path tables or small initializer functions.
- Keep comments useful: document subsystem purpose, not obvious assignments.

## Resources

- 42 Intranet cub3D subject PDF
- [Raycasting Tutorial Part 1: Introduction and basic concepts (3DSage)](https://www.youtube.com/watch?v=gYRrGTC7GtA&ab_channel=3DSage)
- [Raycasting Tutorial Part 2: C implementation (3DSage)](https://www.youtube.com/watch?v=fRu8kjXvkdY&ab_channel=3DSage)
- [Raycasting Tutorial Part 3: Textures and optimization (3DSage)](https://www.youtube.com/watch?v=w0Bm4IA-Ii8&ab_channel=3DSage)
- [Raycasting Tutorial Part 4: Sprites and objects (3DSage)](https://www.youtube.com/watch?v=8j0gakEHJuI&ab_channel=3DSage)
- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- [MiniLibX Linux Repository](https://github.com/42Paris/minilibx-linux)
- [Lode Vandevenne Raycasting Guide](https://lodev.org/cgtutor/raycasting.html)
- [Wikipedia: Ray casting](https://en.wikipedia.org/wiki/Ray_casting#Beyond_raycasting)

### Team

- dbouizem: https://github.com/dbouizem/
- brrr1: https://github.com/Basurita-Bebe

### AI Usage

AI was used as an assistant for:

- proposing refactors,
- generating edge-case ideas for parser/map validation tests,
- reviewing movement/collision robustness,
- reviewing README structure and wording.

All generated suggestions were manually reviewed, adapted, compiled, and tested
before integration.
