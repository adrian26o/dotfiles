#! /usr/bin/env python3

from libqtile.command.client import InteractiveCommandClient
c = InteractiveCommandClient()
icon="%{F#383E49}"
focused="%{F#ABB2BF}"

ws = [icon for i in range(9)]

ws_focused = c.layout.info()["group"]
ws_focused = int(ws_focused)

ws[ws_focused - 1] = focused
print(" ".join(ws))
