#ifndef __algorithm_Bag_Bag_HPP__
# define __algorithm_Bag_Bag_HPP__

# include <utility>

namespace algorithm {
template <class Container>
struct Bag {
    using iterator = typename Container::iterator;

    Container container;
    iterator EndOfBag = {};

    template <class ...Args>
    constexpr Bag(Args&& ...args): container(std::forward<Args>(args)...) {
    }
};

template <class It>
struct Bag_view {
    It beg, EndOfBag, end;

    auto push();
    auto size();
    auto is_empty();
};
} /* algorithm */
#endif
