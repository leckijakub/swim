#!/usr/bin/env python3

import sys
import os
from pathlib import Path

SCRIPT_DIR = Path(os.path.dirname(os.path.realpath(__file__)))
WORKSPACE_DIR = (SCRIPT_DIR / "../..").resolve()


def set_json_file_value(json_filepath: Path, property: str, key: str, value: str):
    import json

    with open(json_filepath) as read_file:
        data = json.load(read_file)
        data[property][key] = value

    with open(json_filepath, "w") as write_file:
        json.dump(data, write_file, indent=4)


if not len(sys.argv) == 2:
    sys.exit("Expected exactly one argument - cross compiler path")

cc_path = Path(sys.argv[1])
if not cc_path.exists():
    sys.exit("Passed path does not exists")


for cw_dir in WORKSPACE_DIR.iterdir():
    if cw_dir.name == ".vscode":
        c_cpp_config = cw_dir / "c_cpp_properties.json"
    else:
        c_cpp_config = cw_dir / ".vscode" / "c_cpp_properties.json"
    if not c_cpp_config.is_file():
        continue
    set_json_file_value(c_cpp_config, "env", "armCompilerPath", str(cc_path))
