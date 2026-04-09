# Bonus Architecture

This project keeps bonus code isolated from mandatory code.

## Layout

- `srcs_bonus/noop/api_noop.c`
  - mandatory fallback implementation (no-op API)
- `srcs_bonus/noop/minimap_noop.c`
  - mandatory fallback for minimap entrypoint
- `srcs_bonus/retro/api.c`
  - lifecycle and frame redirection (`retro_init`, `retro_begin`,
    `retro_render`, `retro_shutdown`)
- `srcs_bonus/retro/image.c`
  - bonus image allocation/destruction/pixel read helpers
- `srcs_bonus/retro/upscale.c`
  - nearest-neighbor upscale from low-res framebuffer to output image
- `srcs_bonus/retro/minimap.c`
  - minimap orchestration (layout, radius, dispatch)
- `srcs_bonus/retro/minimap_render.c`
  - minimap buffer clear, world sampling, player marker, final blit
- `srcs_bonus/retro/shading.c`
  - bonus-only distance/faces shading (+ gamma/quantization)
- `srcs_bonus/retro/walls_core.c` + `srcs_bonus/retro/walls_io.c`
  - bonus-only wall tiles (`2..9`) validation/solid rules + texture loading
- `srcs_bonus/doors/*.c`
  - bonus door discovery, interaction, state update and spatial queries

## Rules

- Mandatory build must never depend on bonus internals.
- Public and internal bonus prototypes are in `include/cub3d_bonus.h`.
- Bonus constants live in `include/defines_bonus.h`.
- Bonus runtime state is grouped under `app->bonus`.
- New bonus features should be added in `srcs_bonus/<feature>/`.
- Do not add `_bonus.c` files inside `srcs/`.

## Runtime Flow

```text
draw_frame()
  -> retro_begin()
  -> draw background + raycast + minimap
  -> retro_render()
```

The bonus path renders into a low-resolution framebuffer, then upscales into
the final output image before the single window blit.

## Testing

- `make test_bonus`
- `tests/run_bonus.sh`

The bonus test suite now checks:
- bonus symbol linkage,
- parser/init failure paths,
- multiple bonus smoke maps,
- large-map runtime survival.
