#ifndef  __snake_snake_HPP__
# define __snake_snake_HPP__

# include <ncurses.h>

namespace snake {
struct position
{
    int x = 0;
    int y = 0;

    constexpr void move(int new_x, int new_y) noexcept
    {
	x = new_x;
	y = new_y;
    }
}; 

enum class direction: unsigned char 
{
    up    = 0,
    down  = 1,
    right = 2,
    left  = 3
};

class snake
{
    WINDOW *win;

    char snake_body_ch;
    char treat_ch;
    position curr_pos;

    enum class State: unsigned char {
	running  = 0,
	paused   = 1,
	error    = 2,
	finished = 3
    } state = State::paused;
    const char *msg = nullptr;

    void mvaddch();

public:
    snake(WINDOW *win_arg, char snake_body_ch_arg = '#', char treat_ch_arg = 'O') noexcept: 
	win{win_arg}, snake_body_ch{snake_body_ch_arg}, treat_ch{treat_ch_arg}
    {
	curr_pos.move(getmaxx(win) / 2, getmaxy(win) / 2);

	mvwaddch(win, curr_pos.y, curr_pos.x, snake_body_ch);
    }
};
}

#endif
