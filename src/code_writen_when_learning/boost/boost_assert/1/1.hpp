#ifndef __1_HPP__
# define __1_HPP__
#include <boost/assert.hpp>
namespace A {
void F() noexcept {
    BOOST_ASSERT(false);
}
} /* 1 */
#endif
