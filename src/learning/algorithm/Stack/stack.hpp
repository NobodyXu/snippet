#ifndef __nobodyxu_wheels_Stacks_stack_HPP__
# define __nobodyxu_wheels_Stacks_stack_HPP__

# include <utility>
# include <vector>

namespace nxwheels {
template <class T, template <class...> class Container>
struct stack {
    using underlying_type = Container<T>;

    underlying_type underlying_container;

    auto& top()       noexcept { return underlying_container.back(); }
    auto& top() const noexcept { return underlying_container.back(); }

    auto topIt()       noexcept { return --underlying_container.end(); }
    auto topIt() const noexcept { return --underlying_container.end(); }

    void push(const T &value)  { underlying_container.push_back(value); }
    void push(      T &&value) { underlying_container.push_back(std::move(value)); }

    template <class ...Args>
    void emplace(Args &&...args) { underlying_container.emplace_back(std::forward<Args>(args)...); }

    constexpr bool empty() const noexcept { return underlying_container.empty(); }
};
} /* nxwheels */
#endif
