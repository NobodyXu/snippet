#ifndef __nobodyxu_wheels_helper_ScopeGuard_HPP__
# define __nobodyxu_wheels_helper_ScopeGuard_HPP__

# include <utility>
# include "inheritable_save_size_function_ref.hpp"

namespace nxwheels {
template <class T>
class ScopeGuard1 {
    T obj;

    constexpr auto& get_value()       noexcept { return obj; }
    constexpr auto& get_value() const noexcept { return obj; }
};
} /* nxwheels */
#endif
