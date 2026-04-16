# Bonus Architecture

This file is the single reference for project structure, runtime flow, and
bonus-mode conventions that are easy to forget during correction or future
refactors.

## Project Layout

The repository is split between mandatory code in `srcs/` and bonus-only code
in `srcs_bonus/`.

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
- `docs/`
  Project documentation.

## Bonus Directory Map

- `retro/`
  Low-resolution framebuffer, upscale pass, minimap, bonus wall rules, wall
  texture loading, animated wall selection, and shading.
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

## Key Bonus Integration Files

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

## Runtime Flow

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

The bonus renderer draws the world into a low-resolution framebuffer first.
`retro_render()` then upscales it to the output image before the window blit.
The HUD is drawn last so it stays sharp and readable.

## Controls

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
| `F4` | `KEY_F4` | Bonus/retro display control |
| Mouse move | `EVENT_MOUSEMOVE` | Mouse look |
| Scroll up/down | `BUTTON_SCROLL_UP`, `BUTTON_SCROLL_DOWN` | Minimap zoom |

## Map Characters

Mandatory parsing still supports the subject map characters:

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
| `BONUS_DOOR_SET` | `ABCDFGHIJKLMOPQRTUVXYZ` | Door-capable bonus tiles |
| `BONUS_PLAYER_SET` | `NSEWBCFGHIJKLMOPQRTUVXYZ` | Player start or bonus door letters |
| `BONUS_WALL_SYMBOL_SET` | punctuation symbols | Bonus symbol wall tiles |
| `BONUS_SPRITE_SET` | `*@)/` | Bonus sprites and pickups |

Numeric bonus wall tiles are `2` to `9`.

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
| `O` | 3 | `BONUS_WALL_O1_XPM`, `BONUS_WALL_O2_XPM`, `BONUS_WALL_O3_XPM` |
| `P` | 3 | `BONUS_WALL_P1_XPM`, `BONUS_WALL_P2_XPM`, `BONUS_WALL_P3_XPM` |
| `Q` | 3 | `BONUS_WALL_Q1_XPM`, `BONUS_WALL_Q2_XPM`, `BONUS_WALL_Q3_XPM` |
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
| Level 2 area | `G` to `N` | `textures/bonus/walls/wall_a/` |
| Level 3 gray symbols | `!`, `"`, `#`, `$`, `%`, `&` | `textures/bonus/walls/wall_g/` |
| Level 4 tech | `D`, `E`, `F` | `textures/bonus/walls/wall_t/` |
| Level 5 computer | `+`, comma, `-` | `textures/bonus/walls/wall_c/` |
| Level 6 marble | `R` to `Z` | `textures/bonus/walls/wall_m/` |
| Level 7 flesh | `'` | `textures/bonus/walls/wall_f/` |
| Level 8 exit | `8`, `9`, `A`, `B`, `C` | `textures/bonus/walls/wall_e/` |
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

## Verification

Use these checks after touching bonus code:

```sh
norminette include srcs srcs_bonus
make
make bonus
make test_bonus
```

If `make test_bonus` fails with `mlx_init failed`, the environment probably has
no X11 display. Parser-only failures are still meaningful; runtime smoke tests
need a graphical session.
