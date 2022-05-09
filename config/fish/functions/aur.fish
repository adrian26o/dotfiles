#!/usr/bin/env fish

function aur
	echo (set_color cyan)Opening aur
	open https://aur.archlinux.org/ &> /dev/null
end
