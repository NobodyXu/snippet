#include <ncurses.h>
#include "Assert.hpp"

int main(int argc, char* argv[])
{
    initscr();

    //cbreak();
    Assert_curses(halfdelay(1) == OK);
    Assert_curses(noecho());
    Assert_curses(keypad(stdscr, true));
    Assert_curses(intrflush(stdscr, false));

    int row = 0, column = 0, maxrow, maxcolumn;
    getmaxyx(stdscr, maxrow, maxcolumn);
    char ch = '#';

    do {

	switch (getch()) {
	    case KEY_DOWN:
		++row;
		break;
	    case KEY_UP:
		--row;
		break;
	    case KEY_LEFT:
		--column;
		break;
	    case KEY_RIGHT:
		++column;
		break;
	    case '\\':
		//ch = Getch();
		break;
	    default:
		goto out;
	}

	continue;
out:
	break;
    } while(true);

    return 0;
}
