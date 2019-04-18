#!/usr/bin/env bash
time $(echo "$1" | "$2" > /dev/null)
