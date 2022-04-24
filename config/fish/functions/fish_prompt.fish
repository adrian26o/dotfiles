function separator
	echo -n " "
end

function newline
	echo " "
end

function _git_exit_code
git status &> /dev/null
set -g git_exit_code $status
end

function git_branch
	if test $git_exit_code -eq 0
		set_color brred
		echo -n (git rev-parse --abbrev-ref HEAD)
		set_color normal
		separator
	end
end

function git_changes
	if test $git_exit_code -eq 0
		# number of diffs
		set -l nod \
		(git status -s | wc -l)
		if test ! $nod -eq 0
			set_color red
			echo -n (set_color -i)"[n]"(set_color red) $nod
			set_color normal
			separator
		end
	end
end

function git_push
if test $git_exit_code -eq 0
	# number of pushs
	
	set -l nop (git log --branches --not --remotes --oneline | wc -l)

	set -l remotes (git remote | wc -l)

	if test ! $nop -eq 0 \
	-a ! $remotes -eq 0
		set_color red
		echo -n "↑" $nop
		set_color normal
		separator
	end
end
end

function path
	set_color cyan
	echo -n (pwd | sed    "s|^$HOME|~|")
	set_color normal
	separator
end

function now
	set_color yellow
	echo -n '' (date +%H:%M)
	set_color normal
	separator
end

function fish_prompt
	_git_exit_code
	echo -n (set_color brmagenta)">"(set_color cyan)">"(set_color brmagenta)">" (set_color cyan)(path)
	if test $git_exit_code -eq 0
		git_branch
		git_changes
		git_push
	end
	echo -n (set_color -o brwhite)"◈  "
end
