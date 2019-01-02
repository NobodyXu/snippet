#include <ncurses.h>
#include <clocale>
#include <utility>
#include <cstdlib>
#include <cstdio>

[[noreturn]] void Assert_failure(const char *s) noexcept
{
    std::fprintf(stderr, "%s\n", s);
    std::exit(1);
}

#define Assert(cond) if (__builtin_expect(!(cond), false)) Assert_failure("Assertion " #cond " fails.")

struct ncurses_mode
{
    ncurses_mode() noexcept
    {
	Assert(initscr());
    }
    ~ncurses_mode()
    {
	Assert(endwin() != ERR);
    }
};

template <class F>
void update(F &&f)
{
    box(stdscr, 0, 0);
    (std::forward<F>(f))();
    
    Assert(refresh() != ERR);
}

auto get_screen_size() noexcept
{
    std::pair<int, int> max_size;
    getmaxyx(stdscr, max_size.first, max_size.second);

    --max_size.first, --max_size.second;

    return max_size;
}

char Getch() noexcept
{
    int ret = getch();
    if (ret == ERR)
	Assert_failure("Assertion getch != ERR fails.");
    return ret;
}

int main(int argc, char* argv[])
{
    Assert(std::setlocale(LC_ALL, ""));
    ncurses_mode ncurse_mode_v{};

    cbreak();
    noecho();
    keypad(stdscr, true);

    int row = 0, column = 0;
    char ch = '#';

    do {
	update([&]() noexcept { Assert(mvaddch(row, column, ch) == OK); });

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
		ch = Getch();
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
