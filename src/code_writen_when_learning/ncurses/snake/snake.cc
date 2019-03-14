#include "snake.hpp"

#include <cstddef>
#include <vector>// std::vector<bool>

struct block;
struct snake_internal;

struct block
{
    size_t x;
    size_t y;
};

// (226 * 56) * 12 / 2 / 1024  
// round buffer
struct snake_internal
{
    //std::vector<line> lines;
};

namespace snake {
class snake
{
    position curr_pos;

public:
    snake(position init_pos) noexcept:
	curr_pos{init_pos} 
    {}

};

snake* make_snake(position init_pos) noexcept
{
    return new snake{init_pos};
}
}
