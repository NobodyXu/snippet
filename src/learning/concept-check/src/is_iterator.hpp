#ifndef __concept_check_is_iterator_HPP__
#define __concept_check_is_iterator_HPP__
# include "basic_concepts.hpp"
# include "is_swappable_with.hpp"
# include "has_operator_overload_functions.hpp"
# include "impl/macro/define_CONCEPT_T.hpp"
# include "impl/iterator_traits_type_alias.hpp"
namespace concept_check {
template <class T, class Tag>//T is not expected to be a reference or a cv-qualified type.
struct _is_It {};

namespace impl {
template <class T>//T is not expected to be a reference or a cv-qualified type.
CONCEPT_T is_cp_dtor_swap_v{is_copiable_v<T> && is_destructible_v<T> && is_swappable_v<T&>};
template <class T>//T is not expected to be a reference or a cv-qualified type.
CONCEPT_T is_pre_inc_deref_v{is_pre_incrementable_v<T&> && has_dereferenceable_v<T>};
}//namespace impl

# define _DEF_is_It(TAG, PRE_COND, CHECK_COND)                                      \
template <class T>/* T is not expected to be a reference or a cv-qualified type. */ \
struct _is_It<T, TAG > {                                                            \
    constexpr bool operator () () const noexcept {                                  \
        if constexpr(PRE_COND) return CHECK_COND;                                   \
        else                   return false;                                        \
    }                                                                               \
    constexpr operator bool () const noexcept { return (*this)(); }                 \
    static CONCEPT_T value{_is_It{}};                                               \
};
# define DEF_is_It(TAG, PRE_COND, CHECK_COND) _DEF_is_It(std:: TAG, PRE_COND, CHECK_COND)

_DEF_is_It(void, impl::is_cp_dtor_swap_v<T> && impl::is_pre_inc_deref_v<T> && has_std_iterator_traits_v<T>)
DEF_is_It(output_iterator_tag, _is_It_v<T>, is_post_incrementable_v<T>)
DEF_is_It(input_iterator_tag, _is_It_v<T>, is_EqualOrNot_Comparable_v<T> && is_dereferenceable_v<T> &&)

# undef _DEF_is_It
# undef DEF_is_It

template <class T, class Tag = void>//T is not expected to be a reference or a cv-qualified type.
CONCEPT_T is_It_v{_is_It<T, Tag>{} && is_It_tag_v<T, Tag>};
template <class T, class Tag>//T is not expected to be a reference or a cv-qualified type.
CONCEPT_T is_mutable_It_v{_is_It<T, Tag>{} && is_mutable_It_tag_v<T, Tag>};
}
# include "impl/macro/define_CONCEPT_T.hpp"
#endif
