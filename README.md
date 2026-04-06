*This project has been created as part of the 42 curriculum by brrr1, dbouizem.*

# cub3D

## Description

`cub3D` is a raycasting project inspired by Wolfenstein 3D.
The goal is to render a first-person 3D view from a 2D `.cub` map using MiniLibX,
with:
- directional wall textures (`NO`, `SO`, `WE`, `EA`),
- floor and ceiling colors (`F`, `C`),
- player movement and camera rotation,
- strict map parsing and validation.

## Instructions

### Requirements

- Linux (X11)
- `cc`
- `make`

### Build

```bash
make
```

### Run

```bash
./cub3D tests/validation/good.cub
```

### Controls

- `W`/`Z`: move forward
- `S`: move backward
- `A`/`Q`: strafe left
- `D`: strafe right
- `Left Arrow`: rotate left
- `Right Arrow`: rotate right
- `ESC`: quit
- Window close button (red cross): quit cleanly

### Useful commands

```bash
make test
make ci
make asan
norminette srcs include
```

## Project Organization

| Issue | Owner | Related Phases | Branch |
|------|------------|-------------|--------|
| Issue 1 — `.cub` file reading and config parsing | A + B | Phase 0: Architecture<br>Phase 1: Setup<br>Phase 2: Config parsing | `1-parsing-cub-file` |
| Issue 2 — Full map extraction and validation | B | Phase 3: Map validation | `2-map-validation` |
| Issue 3 — Game and MiniLibX initialization | A | Phase 4: MLX + Textures | `3-mlx-init` |
| Issue 4 — Player system and input handling | B | Phase 5: Player system | `4-player-inputs` |
| Issue 5 — Ray-casting implementation | A | Phase 6: Raycasting | `5-raycasting` |
| Issue 6 — Final rendering with textures, floor, and ceiling | B | Phase 7: Textured render | `6-textured-render` |
| Issue 7 — Errors, cleanup, tests, and polishing | A + B | Phase 8: Polish | `7-polish` |

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

### AI usage

AI was used as an assistant for:
- proposing refactors,
- generating edge-case ideas for parser/map validation tests,
- reviewing movement/collision robustness.

All generated suggestions were manually reviewed, adapted, compiled, and tested
before integration.
