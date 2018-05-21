#ifndef __2_HPP__
# define __2_HPP__
#include <boost/assert.hpp>
namespace B {
void F() noexcept {
    BOOST_ASSERT(false);
}
} /* 2 */
#endif
