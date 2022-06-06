#! /usr/bin/env python3
import json
from libqtile.command.client import CommandClient
from os import environ, path, system
from sys import argv

home = environ["HOME"]
argv = argv[1:]


def main():
    colors = open(path.join(home, ".config", "qtile", "colors.json"), "r")
    colors = json.loads(colors.read())

    if len(argv) < 1:
        print("This program needs at least one argument")
        exit(1)

    if len(argv) > 1:
        print("This program only acept one argument")
        exit(1)

    data = None

    for color, color_data in colors.items():
        if argv[0] == color:
            data = color_data

    if data is None:
        print("Colorscheme doesn't exist")
        exit(2)

    alacritty_change_color(data["alacritty"])
    dunst_change_color(data["dunst"])
    eww_change_color(data["eww"])
    polybar_change_color(data["polybar"])
    change_gtk_theme(data["gtk-theme"])
    change_wallpaper(data["wallpaper"])


def eww_change_color(color: str) -> None:
    eww_file = path.join(home, ".config/eww/eww.scss")

    with open(eww_file, "r") as scss:
        text = scss.read()
        text = text.split("\n")

        _import = f"@use 'colors/{color}' as colors;"
        text[0] = _import

        text = "\n".join(text)
        with open(eww_file, "w") as file:
            file.write(text)


def polybar_change_color(color: str):
    polybar_file = path.join(home, ".config/polybar/config.ini")
    color_file = path.join(home, f".config/polybar/colors/{color}")

    with open(polybar_file, "r") as config:
        text = config.read()
        text = text.split("\n")
        text[1] = f"include-file = {color_file}"
        text = "\n".join(text)

        with open(polybar_file, "w") as file:
            file.write(text)

    system("killall -q polybar")
    system('while pgrep -u $UID -x polybar > /dev/null; do sleep 1; done')
    system('polybar &')


def alacritty_change_color(color: str):
    alacritty_file = path.join(home, ".config/alacritty/alacritty.yml")
    color_file = path.join(home, f".config/alacritty/colors/{color}")

    with open(alacritty_file, "w") as config:
        with open(color_file, "r") as color:
            config.write(color.read())


def dunst_change_color(color: str):
    dunst_file = path.join(home, ".config/dunst/dunstrc")
    color_file = path.join(home, f".config/dunst/colors/{color}")

    with open(dunst_file, "w") as config:
        with open(color_file, "r") as color:
            config.write(color.read())

    system("killall -q dunst")
    system('while pgrep -u $UID -x dunst > /dev/null; do sleep 1; done')
    system('dunst &')


def change_gtk_theme(theme: str):
    gtk_file = path.join(home, ".config/gtk-3.0/settings.ini")

    with open(gtk_file, "r") as config:
        text = config.read()
        text = text.split("\n")
        text[1] = f"gtk-theme-name={theme}"
        text = "\n".join(text)

        with open(gtk_file, "w") as file:
            file.write(text)


def change_wallpaper(wallpaper: str):
    qtile_file = path.join(home, ".config/qtile/config.py")

    with open(qtile_file, "r") as config:
        text = config.read()
        text = text.split("\n")
        for i, line in enumerate(text):
            if line.startswith("wallpaper_file"):
                text[i] = f"wallpaper_file = '{wallpaper}'"

        text = "\n".join(text)

        with open(qtile_file, "w") as file:
            file.write(text)

    c = CommandClient()
    c.call("reload_config")


if __name__ == '__main__':
    main()
