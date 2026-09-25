#!/usr/bin/env python3
"""Convert a binary PPM (P6) image to PNG using only the Python stdlib.

Used by CI to turn miniRT's headless PPM render into a viewable screenshot
artifact without pulling in ImageMagick/Pillow.
"""
import struct
import sys
import zlib


def read_ppm(path):
    with open(path, "rb") as f:
        data = f.read()
    if data[:2] != b"P6":
        raise ValueError("not a binary PPM (P6) file")
    i = 2
    values = []
    while len(values) < 3:
        while data[i:i + 1].isspace():
            i += 1
        if data[i:i + 1] == b"#":
            while data[i:i + 1] != b"\n":
                i += 1
            continue
        j = i
        while not data[j:j + 1].isspace():
            j += 1
        values.append(int(data[i:j]))
        i = j
    i += 1
    width, height, _maxval = values
    pixels = data[i:i + width * height * 3]
    return width, height, pixels


def write_png(path, width, height, pixels):
    def chunk(tag, payload):
        return (
            struct.pack(">I", len(payload))
            + tag
            + payload
            + struct.pack(">I", zlib.crc32(tag + payload) & 0xFFFFFFFF)
        )

    ihdr = struct.pack(">IIBBBBB", width, height, 8, 2, 0, 0, 0)
    stride = width * 3
    raw = bytearray()
    for y in range(height):
        raw.append(0)
        raw.extend(pixels[y * stride:(y + 1) * stride])
    idat = zlib.compress(bytes(raw), 9)
    with open(path, "wb") as f:
        f.write(b"\x89PNG\r\n\x1a\n")
        f.write(chunk(b"IHDR", ihdr))
        f.write(chunk(b"IDAT", idat))
        f.write(chunk(b"IEND", b""))


def main():
    if len(sys.argv) != 3:
        print(f"usage: {sys.argv[0]} input.ppm output.png", file=sys.stderr)
        return 1
    width, height, pixels = read_ppm(sys.argv[1])
    write_png(sys.argv[2], width, height, pixels)
    print(f"wrote {sys.argv[2]} ({width}x{height})")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
