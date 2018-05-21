#!/bin/bash
exec i3-nagbar -m "Do you wanna to be locked?"\
	       -b "lock" "~/try/bash/infinite_loop_plus_i3lock.sh"\
	       -t warning
	       #-b "lock" "urxvtc -e i3lock &"\
