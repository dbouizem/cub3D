#!/usr/bin/env python3
"""
Convert PNG textures to XPM and resize them to a fixed square size.

Usage examples:
  python3 tools/png_to_xpm.py --src textures/wallD
  python3 tools/png_to_xpm.py --src textures --dst textures_xpm --size 128
  python3 tools/png_to_xpm.py --src textures --overwrite
"""

from __future__ import annotations

import argparse
import shutil
import subprocess
import sys
from pathlib import Path


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Convert all .png files recursively to .xpm with a fixed size."
    )
    parser.add_argument(
        "--src",
        required=True,
        type=Path,
        help="Source directory to scan recursively for PNG files.",
    )
    parser.add_argument(
        "--dst",
        type=Path,
        default=None,
        help=(
            "Destination root directory. If omitted, files are written next to "
            "their PNG source."
        ),
    )
    parser.add_argument(
        "--size",
        type=int,
        default=128,
        help="Target size in pixels (size x size). Default: 128.",
    )
    parser.add_argument(
        "--overwrite",
        action="store_true",
        help="Overwrite existing .xpm files.",
    )
    parser.add_argument(
        "--dry-run",
        action="store_true",
        help="Show planned conversions without writing files.",
    )
    return parser.parse_args()


def find_png_files(src_root: Path) -> list[Path]:
    files: list[Path] = []
    for path in src_root.rglob("*"):
        if path.is_file() and path.suffix.lower() == ".png":
            files.append(path)
    files.sort()
    return files


def output_path_for(src_png: Path, src_root: Path, dst_root: Path | None) -> Path:
    rel = src_png.relative_to(src_root).with_suffix(".xpm")
    if dst_root is None:
        return src_png.with_suffix(".xpm")
    return dst_root / rel


def run_convert(src_png: Path, dst_xpm: Path, size: int) -> None:
    # Force exact square size to keep a consistent texture atlas style.
    cmd = [
        "convert",
        str(src_png),
        "-resize",
        f"{size}x{size}!",
        str(dst_xpm),
    ]
    subprocess.run(cmd, check=True)


def main() -> int:
    args = parse_args()

    if shutil.which("convert") is None:
        print("Error: 'convert' (ImageMagick) is not installed.", file=sys.stderr)
        return 1

    src_root = args.src.resolve()
    if not src_root.exists() or not src_root.is_dir():
        print(f"Error: source directory not found: {src_root}", file=sys.stderr)
        return 1

    if args.size <= 0:
        print("Error: --size must be > 0.", file=sys.stderr)
        return 1

    dst_root = args.dst.resolve() if args.dst else None
    png_files = find_png_files(src_root)

    if not png_files:
        print(f"No PNG files found in: {src_root}")
        return 0

    converted = 0
    skipped = 0
    failed = 0

    for src_png in png_files:
        dst_xpm = output_path_for(src_png, src_root, dst_root)

        if dst_xpm.exists() and not args.overwrite:
            print(f"skip (exists): {dst_xpm}")
            skipped += 1
            continue

        print(f"{src_png} -> {dst_xpm}")

        if args.dry_run:
            converted += 1
            continue

        dst_xpm.parent.mkdir(parents=True, exist_ok=True)
        try:
            run_convert(src_png, dst_xpm, args.size)
            converted += 1
        except subprocess.CalledProcessError:
            print(f"failed: {src_png}", file=sys.stderr)
            failed += 1

    print(
        f"Done. converted={converted} skipped={skipped} failed={failed} "
        f"size={args.size}x{args.size}"
    )

    return 1 if failed > 0 else 0


if __name__ == "__main__":
    raise SystemExit(main())
