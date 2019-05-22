#ifndef __concept_check_has_operator_overload_functions_HPP__
#define __concept_check_has_operator_overload_functions_HPP__
# include "impl/helper_function_declarations.hpp"
# include "impl/rm_cvref.hpp"
# include "impl/iterator_traits_type_alias.hpp"
# include "impl/macro/define_fn_check.hpp"
# include "impl/macro/define_CONCEPT_T.hpp"
namespace concept_check {
//Note: create_check_fn_ret_t_test actually defines has_ ... _v and is_ ... _v
create_check_fn_ret_t_test(pre_incrementable, decltype(++create_T<T>()), rm_ref_t<T>&, void)
create_check_fn_ret_t_test(post_incrementable, decltype(create_T<T>()++), rm_ref_t<T>, void)

create_check_fn_ret_t_test(EqualityComparable, decltype(create_T<T>() == create_T<T>()), bool, void)
create_check_fn_ret_t_test(inEqualityComparable, decltype(create_T<T>() != create_T<T>()), bool, void)
template <class T>
CONCEPT_T is_EqualOrNot_Comparable_v{is_EqualityComparable_v<T> && is_inEqualityComparable_v<T>};

/*
 * has_dereferenceable_v
 * This concept veriable should be used when
 *     1. User don't care the return type of *T;
 *     2. User can't make sure that T is an iterator;
 *     3. It_tag<T> == std::output_iterator_tag.
 * Otherwise, use is_dereferenceable_v<T>.
 *Note: has_dereferenceable_v<void*> == True, according to the result of  test/test_has_operator_overload_functions_HPP.cc
 */
create_check_fn_ret_t_test(dereferenceable, decltype(*create_T<T>()), It_ref<rm_cvref_t<T>>, void)
}//namespace concept_check
# include "impl/macro/undef_fn_check.hpp"
# include "impl/macro/undef_CONCEPT_T.hpp"
#endif
