#ifndef __concept_check_iterator_traits_concepts_HPP__
#define __concept_check_iterator_traits_concepts_HPP__
# include "basic_concepts.hpp"
# include "has_operator_overload_functions.hpp"
# include "impl/iterator_traits_type_alias.hpp"
# include "impl/helper_function_declarations.hpp"
# include "impl/macro/define_CONCEPT_T.hpp"
namespace concept_check::iterator_traits {
# include "impl/macro/define_has_member_type.hpp"
create_fn_has_member_type_alias(std_iterator_traits, It_tag<T>)
# include "impl/macro/undef_has_member_type.hpp"

/*
 * Check It_tag.
 * Different from en.cppreference.com/w/cpp/iterator, the tag here can be a user-defined class/union,
 * as long as it can be converted to 1 of the 5 tags(it is allowed to convert to not only 1 tag).
 */
template <class T>//T is not expected to be a reference or a cv-qualified type.
struct is_tag<T, void>: std::bool_constant<is_tag_v<T, std::input_iterator_tag> || is_tag_v<T, std::output_iterator_tag>> {};
template <class T, class Tag>//T, tag is not expected to be a reference or a cv-qualified type.
struct is_tag: std::bool_constant<is_convertible_v<T, Tag>> {};
template <class T, class Tag>//T, tag is not expected to be a reference or a cv-qualified type.
CONCEPT_T is_tag_v{is_tag<T, Tag>{}};
template <class T, class Tag>//T, tag is not expected to be a reference or a cv-qualified type.
CONCEPT_T is_It_tag_v{is_tag_v<It_tag<T>, Tag>};

template <class T, class Tag>//T, tag is not expected to be a reference or a cv-qualified type.
CONCEPT_T is_mutable_tag_v{is_tag_v<T, Tag> && is_tag_v<T, std::output_iterator_tag>};
template <class T, class Tag>//T, tag is not expected to be a reference or a cv-qualified type.
CONCEPT_T is_mutable_It_tag_v{is_mutable_tag_v<It_tag<T>, Tag>};

template <class T>//T, tag is not expected to be a reference or a cv-qualified type.
CONCEPT_T is_tag_valid_v{is_tag_v<T, void>};
template <class T>//T, tag is not expected to be a reference or a cv-qualified type.
CONCEPT_T is_It_tag_valid_v{is_tag_valid_v<It_tag<T>>};

template <class T>//T is not expected to be a reference or a cv-qualified type.
CONCEPT_T is_It_val_valid_v{!(is_void_v<T> || is_reference_v<It_val<T>>)};
template <class T>//T is not expected to be a reference or a cv-qualified type.
CONCEPT_T is_It_ref_valid_v{is_convertible_cp_elided_ver_v<It_ref<T>, It_val<T>>};
template <class Ptr, class Val>//Ptr, Val is not expected to be a reference or a cv-qualified type.
CONCEPT_T is_ptr_valid_v{has_dereferenceable_v<Ptr> && is_convertible_cp_elided_ver_v<decltype(*create_T<Ptr>()), Val&>};
template <class T>//T is not expected to be a reference or a cv-qualified type.
CONCEPT_T is_It_ptr_valid_v{is_ptr_valid_v<It_ptr<T>, It_val<T>>};

template <class T>//T is not expected to be a reference or a cv-qualified type.
CONCEPT_T is_diff_t_valid_v{is_signed_v<T>};
template <class T>//T is not expected to be a reference or a cv-qualified type.
CONCEPT_T is_It_diff_t_valid_v{is_diff_t_valid_v<It_diff_t<T>>};

template <class T>//T is not expected to be a reference or a cv-qualified type.
CONCEPT_T is_iterator_traits_valid_v{is_It_tag_valid_v<T> && is_It_val_valid_v<T> && is_It_ref_valid_v<T> && is_It_ptr_valid_v<T> && is_It_diff_t_valid_v<T>}
template <class T, class Tag>//T is not expected to be a reference or a cv-qualified type.
CONCEPT_T is_It_traits_valid_as_v{is_It_val_valid_v<T> && is_It_ref_valid_v<T> && is_It_ptr_valid_v<T> && is_It_diff_t_valid_v<T>&& is_It_tag_v<T, Tag>};
}//namespace concept_check::iterator_traits
# include "impl/macro/undef_CONCEPT_T.hpp"
#endif
