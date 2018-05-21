#!/bin/bash
exec i3-nagbar -m "What do you want to do?"				       \
	       -b "lock" "i3lock &"					       \
	       -b "hibernate" "exec echo "disk" | sudo -A tee /sys/power/state && i3lock"\
	       -t warning
