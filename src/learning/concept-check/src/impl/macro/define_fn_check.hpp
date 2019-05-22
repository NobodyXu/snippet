//C++17
# include "basic_concepts.hpp"
# include "impl/disambiguation_types.hpp"

//All the macro here should be placed inside the namespace concept_check, or namespaces inside concept_check
#ifndef create_has_fn_test
# define create_has_fn_test(fn_name, ret_t_of_fn_to_test, not_result_t)                     \
namespace impl {                                                                            \
template <class T> auto has_## fn_name (disambiguation_t1) noexcept -> ret_t_of_fn_to_test; \
template <class T> auto has_## fn_name (disambiguation_t2) noexcept -> not_result_t;        \
template <class T> using ret_t_of_has_ ##fn_name = decltype(has_## fn_name <T>(disambiguation_t1{}));\
}                                                                                           \
template <class T> CONCEPT_T has_## fn_name ##_v{!is_same_v<impl::ret_t_of_has_ ##fn_name<T>, not_result_t>};
#endif

#ifndef create_check_fn_ret_t_test
# define create_check_fn_ret_t_test(fn_name, ret_t_of_fn_to_test, result_t, not_result_t)\
create_has_fn_test(fn_name, ret_t_of_fn_to_test, not_result_t)                           \
_create_check_fn_ret_t_test(fn_name, ret_t_of_fn_to_test, result_t)
#endif

#ifndef _create_check_fn_ret_t_test
# define _create_check_fn_ret_t_test(fn_name, ret_t_of_fn_to_test, result_t)\
namespace impl {                                                            \
template <class T> CONCEPT_T is_## fn_name () noexcept {                          \
    if constexpr(has_## fn_name ##_v<T>) return is_convertible_cp_elided_ver_v< ret_t_of_fn_to_test , result_t >;\
    else                                 return 0;                                                           \
}                                                                           \
}                                                                           \
template <class T> CONCEPT_T is_## fn_name ##_v = impl::is_## fn_name <T>();
#endif
