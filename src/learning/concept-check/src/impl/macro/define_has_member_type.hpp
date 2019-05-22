#include "impl/disambiguation_types.hpp"
#include "impl/macro/define_CONCEPT_T.hpp"

//The macro should be used inside namespace concept_check
#ifndef create_fn_has_member_type_alias
# define create_fn_has_member_type_alias(fn_name, how_to_get)                 \
namespace impl {                                                              \
template <class T>                                                            \
CONCEPT_T has_ ## fn_name (disambiguation_t2) noexcept { return 0; }\
                                                                              \
template <class T, class = how_to_get>                                        \
CONCEPT_T has_ ## fn_name (disambiguation_t1) noexcept { return 1; }\
}                                                                             \
template <class T>\
CONCEPT_T has_ ## fn_name ##_v {impl::has_ ## fn_name <T>(disambiguation_t1{})};

#include "impl/macro/undef_CONCEPT_T.hpp"
#endif
