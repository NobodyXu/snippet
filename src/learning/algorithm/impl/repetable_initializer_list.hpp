#ifndef __algorithm_impl_repetable_initializer_list_HPP__
# define __algorithm_impl_repetable_initializer_list_HPP__
# include <cstddef>
# include <initializer_list>
# include "algorithm/impl/macro/branch_predict/branch_predict.hpp"
namespace algorithm::impl {
template <class T, template <class...> class init_list = std::initializer_list>
struct repetable_initializer_list: protected init_list<T> {
    std::size_t repetion_ratio = 1;

    typedef init_list<T> Base;
    struct iterator {
        typename Base::iterator curr;
        repetable_initializer_list *list;

        constexpr auto operator++() noexcept -> decltype(auto) { return ++curr; }
        constexpr auto operator++(int) noexcept -> decltype(auto) { return curr++; }
        constexpr bool operator!=(const iterator &other) noexcept {
            if (unlikely(curr == other.curr))
                if (list->repetion_ratio-- > 0) {
                    curr = list->begin().curr;
                    return 1;
                } else
                    return 0;
            else
                return 1;
        }
    };

    constexpr iterator begin() const noexcept { return {Base::begin(), this}; }
    constexpr iterator end() const noexcept { return {Base::end(), this}; }
};
} /* algorithm::impl */
# include "algorithm/impl/macro/branch_predict/undef_branch_predict.hpp"
#endif
