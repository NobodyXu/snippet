#!/usr/bin/env python3

import curses

def main(stdscr):
    curses.start_color()
    curses.use_default_colors()
    # 0 is always black
    for i in range(0, curses.COLORS):
        curses.init_pair(i + 1, i, -1)

    for i in range(1, curses.COLORS + 1):
        stdscr.addstr("A", curses.color_pair(i))
    stdscr.addch("\n")
    for i in range(1, curses.COLORS + 1):
        stdscr.addch("A", curses.color_pair(i))
    stdscr.addch("\n")
    stdscr.addstr(str(curses.COLORS))
    stdscr.refresh()
    stdscr.getch()

curses.wrapper(main)
