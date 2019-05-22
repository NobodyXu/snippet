#ifndef __concept_check_basic_concepts_HPP__
#define __concept_check_basic_concepts_HPP__
# include <type_traits>
# include "impl/macro/define_CONCEPT_T.hpp"
# define DEF_CONCEPT_V_WRAPPER_FOR_STD_T(STD_NAME, COND, ...) DEF_CONCEPT_V(STD_NAME ##_v, (STD_NAME < __VA_ARGS__ >{}()))
# define Introduce_and_Def_Wrappr_for_std_t(STD_NAME, MACRO)\
    using std:: STD_NAME ;\
    MACRO(STD_NAME, , DEF_CONCEPT_V_WRAPPER_FOR_STD_T)
namespace concept_check {
//I define the following stuff because libstdc++ 6.3.0 doesn't have them

Introduce_and_Def_Wrappr_for_std_t(is_default_constructible, DEF_CONCEPT_1);
Introduce_and_Def_Wrappr_for_std_t(is_copy_constructible, DEF_CONCEPT_1);
Introduce_and_Def_Wrappr_for_std_t(is_copy_assignable, DEF_CONCEPT_1);

DEF_CONCEPT_1(is_copiable_v, is_copy_assignable_v<T> && is_copy_constructible_v<T>, DEF_CONCEPT_V);

Introduce_and_Def_Wrappr_for_std_t(is_convertible, DEF_CONCEPT_2);
Introduce_and_Def_Wrappr_for_std_t(is_same, DEF_CONCEPT_2);

/*
 * There's a case which standard semantic of is_convertible can't work well here.
 * Suppose out define_fn_check.hpp relys on standard version of is_convertible
 * #include <iostream>
 * #include "has_operator_overload_functions.hpp"
 * struct A {
 * A(const A&) = delete;
 * A(A&&) = delete;
 * A operator ++ (int) noexcept { auto ret{*this}; ++i; return ret; }
 * int i;
 * };
 * int main() {
 * std::cout << boolalpha << is_pre_incrementable_v<A> << std::endl;
 * }
 * The program above will give you false,
 * For that reason, I wrote another concept here.
 */
DEF_CONCEPT_2(is_convertible_cp_elided_ver_v, (is_same_v<T1, T2> || is_convertible_v<T1, T2>), DEF_CONCEPT_V);

Introduce_and_Def_Wrappr_for_std_t(is_destructible, DEF_CONCEPT_1);
Introduce_and_Def_Wrappr_for_std_t(is_base_of, DEF_CONCEPT_2);

//Note: is_swappable is separated from this file because
//1. libstdc++ 6.3.0 doesn't define it
//2. it will include utility
Introduce_and_Def_Wrappr_for_std_t(is_void, DEF_CONCEPT_1);
Introduce_and_Def_Wrappr_for_std_t(is_reference, DEF_CONCEPT_1);
Introduce_and_Def_Wrappr_for_std_t(is_signed, DEF_CONCEPT_1);
}
# undef DEF_CONCEPT_V_WRAPPER_FOR_STD_T
# undef Introduce_and_Def_Wrappr_for_std_t
# include "impl/macro/undef_CONCEPT_T.hpp"
#endif
