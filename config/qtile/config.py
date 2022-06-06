###################################################
###################################################
## ______   _ _____ _   _ _   ___   __ _    _  __##
##|__  / | | | ____| \ | | \ | \ \ / // \  | |/ /##
##  / /| |_| |  _| |  \| |  \| |\ V // _ \ | ' / ##
## / /_|  _  | |___| |\  | |\  | | |/ ___ \| . \ ##
##/____|_| |_|_____|_| \_|_| \_| |_/_/   \_\_|\_\##
###################################################
###################################################

from libqtile import layout
from libqtile.config import Click, Drag, Group, Key, Match, Screen
from libqtile.lazy import lazy
from libqtile.utils import guess_terminal
from os import environ
import subprocess
from libqtile import hook

mod = "mod4"
terminal = guess_terminal()

scripts = environ["HOME"] + "/Scripts"
explorer = "nautilus"

screenshot_folder = environ["HOME"]
record_folder = screenshot_folder
wallpaper_file = '~/Wallpapers/tokyonight/9.png'

keys = [
    # Navigate between windows
    Key([mod], "h", lazy.layout.left(), desc="Move focus to left"),
    Key([mod], "l", lazy.layout.right(), desc="Move focus to right"),
    Key([mod], "j", lazy.layout.down(), desc="Move focus down"),
    Key([mod], "k", lazy.layout.up(), desc="Move focus up"),
    Key([mod], "space", lazy.layout.next(), desc="Move window focus to other window"),
    
    # Move window    
    Key([mod, "shift"], "h", lazy.layout.shuffle_left(), desc="Move window to the left"),
    Key([mod, "shift"], "l", lazy.layout.shuffle_right(), desc="Move window to the right"),
    Key([mod, "shift"], "j", lazy.layout.shuffle_down(), desc="Move window down"),
    Key([mod, "shift"], "k", lazy.layout.shuffle_up(), desc="Move window up"),
    
    # Resize window
    Key([mod, "control"], "h", lazy.layout.grow_left(), desc="Grow window to the left"),
    Key([mod, "control"], "l", lazy.layout.grow_right(), desc="Grow window to the right"),
    Key([mod, "control"], "j", lazy.layout.grow_down(), desc="Grow window down"),
    Key([mod, "control"], "k", lazy.layout.grow_up(), desc="Grow window up"),
    Key([mod], "n", lazy.layout.normalize(), desc="Reset all window sizes"),
    
    # Fullscreen
    Key([mod],"f", lazy.window.toggle_fullscreen(), desc="Toggle fullscreen"),
    
    # Spawn terminal
    Key([mod], "Return", lazy.spawn(terminal), desc="Launch terminal"),
    
    # Floating
    Key([mod,"shift"], "space", lazy.window.toggle_floating(), desc="toggle floating window"),
    
    # Toggle layouts
    Key([mod], "Tab", lazy.next_layout(), desc="Toggle between layouts"),
    
    # Explorer
    Key([mod],"e", lazy.spawn(explorer), desc="Open file explorer"),
    
    # Kill window
    Key([mod, "shift"], "q", lazy.window.kill(), desc="Kill focused window"),
    
    # Reload
    Key([mod, "shift"], "r", lazy.reload_config(), desc="Reload the config"),
    
    # Exit
    Key([mod, "shift"], "e", lazy.shutdown(), desc="Shutdown Qtile"),
    
    # Show Rofi
    Key([mod], "d", lazy.spawn("rofi -show drun"), desc="Execute rofi"),
    
    # Volume Control
    Key([],"XF86AudioRaiseVolume", lazy.spawn(scripts + "/audioControl up"), desc="Raise volume"),
    Key([],"XF86AudioLowerVolume", lazy.spawn(scripts + "/audioControl down"), desc="Lower volume"),
    Key([],"XF86AudioMute", lazy.spawn(scripts + "/audioControl mute"), desc="Toggle muted"),
    
    # Brightness Control
    Key([],"XF86MonBrightnessUp", lazy.spawn(scripts + "/brightnessControl up"), desc="Raise up Brightness"),
    Key([],"XF86MonBrightnessDown", lazy.spawn(scripts + "/brightnessControl down"), desc="Raise up Brightness"),
    
    # Music Control
    Key([], "XF86AudioPlay", lazy.spawn(scripts + "/playerControl toggle"), desc="Toggle pause"),
    Key([], "XF86AudioPrev", lazy.spawn(scripts + "/playerControl prev"), desc="Previous media"),
    Key([], "XF86AudioNext", lazy.spawn(scripts + "/playerControl next"), desc="Next media"),
    
    # Screenshots
    # To clipboard
    Key(["control","shift"],"Print", lazy.spawn("escrotum -C -s"), desc="Selection screenshot to clipboard"),
    Key(["control"],"Print",lazy.spawn("escrotum -C"),desc="Screenshot to clipboard"),

    # To file
    Key(["shift"],"Print",lazy.spawn(f"escrotum -s {screenshot_folder}/%Y-%m-%d-%H%M%S_$wx$h_escrotum.png"), desc="Selection screenshot save into file"),
    Key([],"Print",lazy.spawn(f"escrotum {screenshot_folder}/%Y-%m-%d-%H%M%S_$wx$h_escrotum.png"),desc="Screenshot save into file"),

    # Record
    Key([mod,"shift"],"Print",lazy.spawn(f"{terminal} -e escrotum -r -s {record_folder}/%Y-%m-%d-%H%M%S_$wx$h_escrotum.webm"), desc="Record selection"),
    Key([mod],"Print",lazy.spawn(f"{terminal} -e escrotum -r {record_folder}/%Y-%m-%d-%H%M%S_$wx$h_escrotum.webm"), desc="Record"),

]

groups = [Group(i) for i in "123456789"]

for i in groups:
    keys.extend(
        [
            # mod1 + letter of group = switch to group
            Key(
                [mod],
                i.name,
                lazy.group[i.name].toscreen(),
                desc="Switch to group {}".format(i.name),
            ),
            # mod1 + shift + letter of group = switch to & move focused window to group
            Key(
                [mod, "shift"],
                i.name,
                lazy.window.togroup(i.name),
                desc="Switch to & move focused window to group {}".format(i.name),
            ),
        ]
    )

layouts = [
    layout.Columns(margin=5,border_width=0),
    layout.Max(),
    # Try more layouts by unleashing below layouts.
    # layout.Stack(num_stacks=2),
    # layout.Bsp(),
    # layout.Matrix(),
    # layout.MonadTall(),
    # layout.MonadWide(),
    # layout.RatioTile(),
    layout.Tile(margin=5, border_width=0),
    # layout.TreeTab(),
    layout.VerticalTile(margin=5, border_width=0),
    # layout.Zoomy(),
]

widget_defaults = dict(
    font="Iosevka",
    fontsize=12,
    padding=3,
)
extension_defaults = widget_defaults.copy()

screens = [
    Screen(
    wallpaper=wallpaper_file,
    wallpaper_mode='stretch'
    ),
]

# Drag floating layouts.
mouse = [
    Drag([mod], "Button1", lazy.window.set_position_floating(), start=lazy.window.get_position()),
    Drag([mod], "Button3", lazy.window.set_size_floating(), start=lazy.window.get_size()),
    Click([mod], "Button2", lazy.window.bring_to_front()),
]

dgroups_key_binder = None
dgroups_app_rules = []  # type: list
follow_mouse_focus = True
bring_front_click = False
cursor_warp = False
floating_layout = layout.Floating(
    float_rules=[
        # Run the utility of `xprop` to see the wm class and name of an X client.
        *layout.Floating.default_float_rules,
        Match(wm_class="confirmreset"),  # gitk
        Match(wm_class="makebranch"),  # gitk
        Match(wm_class="maketag"),  # gitk
        Match(wm_class="ssh-askpass"),  # ssh-askpass
        Match(title="branchdialog"),  # gitk
        Match(title="pinentry"),  # GPG key password entry
    ],
    border_width = 0
)
auto_fullscreen = True
focus_on_window_activation = "smart"
reconfigure_screens = True

# If things like steam games want to auto-minimize themselves when losing
# focus, should we respect this or not?
auto_minimize = True

# When using the Wayland backend, this can be used to configure input devices.
wl_input_rules = None


@hook.subscribe.startup_once
def autostart():
    home = environ["HOME"]
    subprocess.Popen([home + '/.config/qtile/autostart.sh'])

wmname = "LG3D"
