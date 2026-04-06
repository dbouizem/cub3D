# Bonus Architecture

This project keeps bonus code isolated from mandatory code.

## Layout

- `srcs_bonus/noop/api_noop.c`
  - mandatory fallback implementation (no-op API)
- `srcs_bonus/retro/api.c`
  - lifecycle and frame redirection (`retro_init`, `retro_begin`,
    `retro_render`, `retro_shutdown`)
- `srcs_bonus/retro/image.c`
  - bonus image allocation/destruction/pixel read helpers
- `srcs_bonus/retro/upscale.c`
  - nearest-neighbor upscale from low-res framebuffer to output image
- `srcs_bonus/retro/shading.c`
  - bonus-only distance/faces shading (+ gamma/quantization)

## Rules

- Mandatory build must never depend on bonus internals.
- Public and internal bonus prototypes are in `include/cub3d_bonus.h`.
- Bonus constants live in `include/defines_bonus.h`.
- New bonus features should be added in `srcs_bonus/<feature>/`.
- Do not add `_bonus.c` files inside `srcs/`.
