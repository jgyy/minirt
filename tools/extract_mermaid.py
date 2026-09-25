#!/usr/bin/env python3
"""Extract the first ```mermaid fenced code block from a Markdown file.

Used by CI to render the architecture diagram embedded in README.md without
keeping a second, easily-out-of-sync copy of the diagram source on disk.
"""
import sys


def extract(markdown_path):
    with open(markdown_path, "r", encoding="utf-8") as f:
        lines = f.readlines()
    inside = False
    block = []
    for line in lines:
        stripped = line.rstrip("\n")
        if not inside and stripped.strip() == "```mermaid":
            inside = True
            continue
        if inside and stripped.strip() == "```":
            break
        if inside:
            block.append(stripped)
    if not block:
        raise ValueError(f"no ```mermaid block found in {markdown_path}")
    return "\n".join(block) + "\n"


def main():
    if len(sys.argv) != 3:
        print(f"usage: {sys.argv[0]} input.md output.mmd", file=sys.stderr)
        return 1
    diagram = extract(sys.argv[1])
    with open(sys.argv[2], "w", encoding="utf-8") as f:
        f.write(diagram)
    print(f"wrote {sys.argv[2]}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
