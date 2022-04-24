#! /usr/bin/env python3
import subprocess, sys

e = subprocess.run(["playerctl metadata"],shell=True,capture_output=True)
e = e.stdout.decode("utf-8").split("\n")

metadata = {}

for i in e:
  if i == "": continue
  try:
    _ = i.split("  ")
    program = _[0].split(" ")[0]
    metadata["program"] = program
    
    datatitle = _[0].split(" ")[1]
    info = [i for i in _[1:] if i.strip() != ""]
    info = " ".join(info)
    info = info.strip()
    if info == "": info = None
    metadata[datatitle] = info
    
  except: pass

if metadata.__len__() <= 0: 
  metadata["xesam:artist"] = "Unknown Artist"
  metadata["xesam:title"] = "Not playing"

_a = [True for i in sys.argv if i == "--artist"]
_t = [True for i in sys.argv if i == "--title"]

artist = metadata["xesam:artist"]
title = metadata["xesam:title"]

if(_a.__len__() >= 1): print(artist)

if(_t.__len__() >= 1): print(title)
