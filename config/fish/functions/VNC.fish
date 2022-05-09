function cloneVNC
	echo (set_color cyan)Cloning display (set_color blue):0(set_color reset)
	x0vncserver -passwordfile ~/.vnc/passwd
end

function newDisplay
	echo (set_color cyan)Creating new display (set_color blue):1(set_color reset)
end
