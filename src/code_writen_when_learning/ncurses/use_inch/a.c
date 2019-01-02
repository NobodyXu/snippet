#include <ncurses.h>

#define hello_str "Hello, world!"

void get_inch(char *str)
{
    int x = 0;

    for (; x != sizeof(hello_str) - 1; ++x)
	str[x] = mvinch(0, x);

    str[x] = '\0';
}

void print_inch()
{
    char str[sizeof(hello_str)];
    get_inch(str);
    addstr(str);
}

int main()
{
    initscr();

    addstr(hello_str);
    getch();

    print_inch();
    getch();

    endwin();
    return 0;
}
