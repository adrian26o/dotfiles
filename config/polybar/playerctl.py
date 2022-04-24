#! /usr/bin/env python3
import subprocess

status = subprocess.run(["playerctl status"],capture_output=True,shell=True)
status = status.stdout.decode("utf-8").strip()

print(status)

