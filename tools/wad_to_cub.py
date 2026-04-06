#!/usr/bin/env python3
"""
Very simple WAD -> .cub converter for cub3D.

It rasterizes Doom linedefs to a grid, flood-fills from Player 1 start,
and emits a closed 2D .cub map approximation.
"""

from __future__ import annotations

import argparse
import os
import struct
from collections import deque


LINEDEF_STRUCT = struct.Struct("<7h")
VERTEX_STRUCT = struct.Struct("<2h")
THING_STRUCT = struct.Struct("<5h")


def lump_name(raw: bytes) -> str:
    return raw.rstrip(b"\x00").decode("ascii", errors="ignore").upper()


def load_wad(path: str):
    with open(path, "rb") as f:
        data = f.read()
    if len(data) < 12:
        raise ValueError("WAD too small")
    ident, numlumps, dirofs = struct.unpack_from("<4sii", data, 0)
    if ident not in (b"IWAD", b"PWAD"):
        raise ValueError("Not a WAD file")
    directory = []
    for i in range(numlumps):
        off = dirofs + i * 16
        filepos, size, name_raw = struct.unpack_from("<ii8s", data, off)
        directory.append(
            {
                "name": lump_name(name_raw),
                "filepos": filepos,
                "size": size,
            }
        )
    return data, directory


def find_map_index(directory, map_name: str) -> int:
    map_name = map_name.upper()
    for i, e in enumerate(directory):
        if e["name"] == map_name:
            return i
    raise ValueError(f"Map lump '{map_name}' not found")


def get_map_lump(data: bytes, directory, map_idx: int, name: str) -> bytes:
    name = name.upper()
    for i in range(map_idx + 1, min(map_idx + 12, len(directory))):
        e = directory[i]
        if e["name"] == name:
            start = e["filepos"]
            end = start + e["size"]
            return data[start:end]
    raise ValueError(f"Lump '{name}' not found after map marker")


def parse_vertices(blob: bytes):
    if len(blob) % VERTEX_STRUCT.size != 0:
        raise ValueError("VERTEXES lump has invalid size")
    out = []
    for i in range(0, len(blob), VERTEX_STRUCT.size):
        out.append(VERTEX_STRUCT.unpack_from(blob, i))
    return out


def parse_linedefs(blob: bytes):
    if len(blob) % LINEDEF_STRUCT.size != 0:
        raise ValueError("LINEDEFS lump has invalid size")
    out = []
    for i in range(0, len(blob), LINEDEF_STRUCT.size):
        v1, v2, flags, special, tag, right, left = LINEDEF_STRUCT.unpack_from(blob, i)
        out.append(
            {
                "v1": v1,
                "v2": v2,
                "flags": flags,
                "special": special,
                "tag": tag,
                "right": right,
                "left": left,
            }
        )
    return out


def parse_things(blob: bytes):
    if len(blob) % THING_STRUCT.size != 0:
        raise ValueError("THINGS lump has invalid size")
    out = []
    for i in range(0, len(blob), THING_STRUCT.size):
        x, y, angle, ttype, flags = THING_STRUCT.unpack_from(blob, i)
        out.append((x, y, angle, ttype, flags))
    return out


def angle_to_cardinal(angle: int) -> str:
    a = angle % 360
    if 45 <= a < 135:
        return "N"
    if 135 <= a < 225:
        return "W"
    if 225 <= a < 315:
        return "S"
    return "E"


def choose_spawn(things):
    preferred = [t for t in things if t[3] == 1]
    if preferred:
        return preferred[0]
    fallback = [t for t in things if t[3] in (1, 2, 3, 4)]
    if fallback:
        return fallback[0]
    raise ValueError("No player start thing found")


def bresenham(x0: int, y0: int, x1: int, y1: int):
    dx = abs(x1 - x0)
    sx = 1 if x0 < x1 else -1
    dy = -abs(y1 - y0)
    sy = 1 if y0 < y1 else -1
    err = dx + dy
    x, y = x0, y0
    while True:
        yield x, y
        if x == x1 and y == y1:
            break
        e2 = 2 * err
        if e2 >= dy:
            err += dy
            x += sx
        if e2 <= dx:
            err += dx
            y += sy


def clamp(v: int, lo: int, hi: int) -> int:
    if v < lo:
        return lo
    if v > hi:
        return hi
    return v


def linedef_is_solid(ld) -> bool:
    # Doom: one-sided lines are walls. Also keep explicitly blocking lines.
    return ld["left"] < 0 or ld["right"] < 0 or (ld["flags"] & 0x0001) != 0


def convert_map(vertices, linedefs, spawn, cell_size: int, margin: int):
    xs = [v[0] for v in vertices] + [spawn[0]]
    ys = [v[1] for v in vertices] + [spawn[1]]
    min_x = min(xs) - margin * cell_size
    max_x = max(xs) + margin * cell_size
    min_y = min(ys) - margin * cell_size
    max_y = max(ys) + margin * cell_size

    w = int((max_x - min_x) / cell_size) + 1
    h = int((max_y - min_y) / cell_size) + 1
    if w < 8 or h < 8:
        raise ValueError("Converted map dimensions are too small")

    grid = [["?" for _ in range(w)] for _ in range(h)]
    wall_cells = set()

    def world_to_grid(wx: int, wy: int):
        gx = int((wx - min_x) / cell_size)
        gy = int((wy - min_y) / cell_size)
        return gx, gy

    for ld in linedefs:
        if not linedef_is_solid(ld):
            continue
        v1 = ld["v1"]
        v2 = ld["v2"]
        if v1 < 0 or v2 < 0 or v1 >= len(vertices) or v2 >= len(vertices):
            continue
        x0, y0 = world_to_grid(vertices[v1][0], vertices[v1][1])
        x1, y1 = world_to_grid(vertices[v2][0], vertices[v2][1])
        for x, y in bresenham(x0, y0, x1, y1):
            if 0 <= x < w and 0 <= y < h:
                wall_cells.add((x, y))

    # Slightly thicken walls to avoid small leaks through rasterization gaps.
    thick = set()
    for x, y in wall_cells:
        for oy in (0,):
            for ox in (0,):
                nx = x + ox
                ny = y + oy
                if 0 <= nx < w and 0 <= ny < h:
                    thick.add((nx, ny))
    wall_cells = thick

    for x, y in wall_cells:
        grid[y][x] = "#"

    sx, sy = world_to_grid(spawn[0], spawn[1])
    sx = clamp(sx, 1, w - 2)
    sy = clamp(sy, 1, h - 2)
    if grid[sy][sx] == "#":
        grid[sy][sx] = "?"

    q = deque()
    q.append((sx, sy))
    grid[sy][sx] = "."
    while q:
        x, y = q.popleft()
        for nx, ny in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)):
            if nx < 0 or ny < 0 or nx >= w or ny >= h:
                continue
            if grid[ny][nx] == "#":
                continue
            if grid[ny][nx] == ".":
                continue
            grid[ny][nx] = "."
            q.append((nx, ny))

    out = []
    for y in range(h):
        row = []
        for x in range(w):
            row.append("0" if grid[y][x] == "." else "1")
        out.append(row)

    # Ensure a closed .cub map: force border walls.
    for x in range(w):
        out[0][x] = "1"
        out[h - 1][x] = "1"
    for y in range(h):
        out[y][0] = "1"
        out[y][w - 1] = "1"

    out[sy][sx] = angle_to_cardinal(spawn[2])
    return out


def write_cub(path: str, grid):
    header = [
        "NO ../textures/freedoom/materials/doom_stone.xpm",
        "SO ../textures/freedoom/materials/doom_metal.xpm",
        "WE ../textures/freedoom/materials/doom_brick.xpm",
        "EA ../textures/freedoom/materials/doom_door.xpm",
        "F 20,20,22",
        "C 70,74,82",
        "",
    ]
    lines = ["".join(r) for r in grid]
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w", encoding="ascii") as f:
        f.write("\n".join(header + lines) + "\n")


def main():
    parser = argparse.ArgumentParser(description="Convert a Doom WAD map to .cub")
    parser.add_argument("--wad", required=True, help="Path to IWAD/PWAD")
    parser.add_argument("--map", default="MAP01", help="Map lump name (eg MAP01/E1M1)")
    parser.add_argument("--out", required=True, help="Output .cub path")
    parser.add_argument("--cell-size", type=int, default=64, help="World units per cell")
    parser.add_argument("--margin", type=int, default=4, help="Margin cells around bbox")
    args = parser.parse_args()

    data, directory = load_wad(args.wad)
    map_idx = find_map_index(directory, args.map)
    vertices = parse_vertices(get_map_lump(data, directory, map_idx, "VERTEXES"))
    linedefs = parse_linedefs(get_map_lump(data, directory, map_idx, "LINEDEFS"))
    things = parse_things(get_map_lump(data, directory, map_idx, "THINGS"))
    spawn = choose_spawn(things)
    grid = convert_map(vertices, linedefs, spawn, args.cell_size, args.margin)
    write_cub(args.out, grid)
    print(f"Wrote {args.out} ({len(grid[0])}x{len(grid)}) from {args.map}")


if __name__ == "__main__":
    main()
