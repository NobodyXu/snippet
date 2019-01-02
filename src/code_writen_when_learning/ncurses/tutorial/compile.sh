#!/bin/sh
clang++-7 -std=c++17 -lncurses -Ofast -fno-exceptions -fno-rtti -flto=full -nodefaultlibs -lc -Wl,--as-needed "$@"
