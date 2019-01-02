#include <ncurses.h>
#include <clocale>
#include <utility>
#include <cstdlib>

[[noreturn]] void Assert_failure(const char *) noexcept
{
    std::exit(1);
}

#define Assert(cond) if (__builtin_expect(!(cond), false)) Assert_failure("Assertion" #cond "fails.")

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

    Assert(getch() != ERR);
    Assert(clear() != ERR);
}

auto get_screen_size() noexcept
{
    std::pair<int, int> max_size;
    getmaxyx(stdscr, max_size.first, max_size.second);

    --max_size.first, --max_size.second;

    return max_size;
}

int main(int argc, char* argv[])
{
    Assert(std::setlocale(LC_ALL, ""));
    ncurses_mode ncurse_mode_v{};

    cbreak();
    noecho();
    keypad(stdscr, true);

    update([]{ printw("Hello, world!\nss"); });

    update([]{ mvprintw(50, 50, "(50, 50)"); });

    update([]{ mvaddch(50, 50, '#'); });


    update([]{
	auto [row, column] = get_screen_size();
	mvaddch(row, column, '#' | A_BOLD | A_UNDERLINE);
    });

    return 0;
}
