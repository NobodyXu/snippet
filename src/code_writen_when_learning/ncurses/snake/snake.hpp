#ifndef  __snake_snake_HPP__
# define __snake_snake_HPP__

# include <cstddef>

namespace snake {
using position = std::size_t;

enum class direction: unsigned char 
{
    up    = 0,
    down  = 1,
    right = 2,
    left  = 3
};

class snake;

snake* make_snake(position init_pos) noexcept;
}

#endif
