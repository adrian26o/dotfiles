#! /usr/bin/env python3
import sys
from gi.repository import Playerctl

player = Playerctl.Player()

title = player.get_title() or "Not playing"
artist = player.get_artist() or "Unknown artist"


_a = [True for i in sys.argv if i == "--artist"]
_t = [True for i in sys.argv if i == "--title"]

if(_a.__len__() >= 1):
    print(artist)

if(_t.__len__() >= 1):
    print(title)
