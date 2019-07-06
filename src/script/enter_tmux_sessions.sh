#!/usr/bin/env sh

if tmux has -t $1; then
    exec tmux attach -t s1
else
    exec tmux new -s s1
fi
