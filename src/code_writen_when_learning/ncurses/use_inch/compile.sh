#!/bin/sh
exec clang-7 -lncurses -Ofast -flto -nodefaultlibs -lc -Wl,--as-needed "$@"
