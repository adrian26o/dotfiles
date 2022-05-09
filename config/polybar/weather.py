#! /usr/bin/env python3
import json, requests

try:
    w = requests.get("https://wttr.in/mexico_merida?format=j1")
except:
    print("Unknown condition")
    exit()

try:
    w = json.loads(w.text)
    print(w["current_condition"][0]["FeelsLikeC"]+"°C")
except:
    print("Unknown condition")
