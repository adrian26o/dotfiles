#! /usr/bin/env bash

polybar qtile &

eww daemon &

picom &

if [ -e ~/.menu ]; then
	rm ~/.menu
fi

