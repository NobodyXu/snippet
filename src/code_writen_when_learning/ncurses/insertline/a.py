#!/usr/bin/env python3

import curses

def main(stdscr):
    stdscr.leaveok(True)
    stdscr.idlok(True)
    curses.curs_set(0)

    while stdscr.getch() != "q":
        stdscr.addstr("a")
        stdscr.refresh()
        stdscr.getch()

        stdscr.insertln()
        stdscr.refresh()
        stdscr.getch()

curses.wrapper(main)
