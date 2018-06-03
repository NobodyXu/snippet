#ifndef __algorithm_Bag_Bag_HPP__
# define __algorithm_Bag_Bag_HPP__
# include <cstddef>
# include <utility>
# include <type_traits>
# include "algorithm/impl/repetable_initializer_list.hpp"
# include "algorithm/range/range.hpp"
namespace algorithm {
template <class Container>
struct Bag {
    typedef typename Container::value_type value_type;
    typedef typename Container::size_type size_t;
    typedef typename Container::difference_type diff_t;
    typedef typename Container::allocator_type alloc_t;
    Container container;

    Bag() = delete;
    Bag(init_list init):
        Container(init.begin(), init.end())
    {
        container.resize(s);
    }


    constexpr bool empty() const noexcept { return container.empty(); }
    constexpr size_t size() const noexcept { return container.size(); }


    void emplace(init_list init) { emplace(init.begin(), init.end()); }

    template <class It1, class It2>
    void emplace(It1 &&it1, const It2 &it2) {
        for(decltype(auto) value: range{it1, it2})
            emplace(value);
    }

    template <class ...Args>
    void emplace(Args &&...args) { container.emplace_back(args...); }


    constexpr auto begin() const noexcept { return container.begin(); }
    constexpr auto end() const noexcept { return container.end(); }

    constexpr auto cbegin() const noexcept { return container.cbegin(); }
    constexpr auto cend() const noexcept { return container.cend(); }
  protected:
    using init_list = std::initializer_list<T>;
    using namespace range;
};
} /* algorithm */
#endif
