#ifndef __concept_check_helper_function_declarations__
#define __concept_check_helper_function_declarations__
//It can only used to test whether a specific operation can be done on a type
//and to check the return type of a function, and can't be used to evaulate the value
namespace concept_check {
template <class T>
T create_T() noexcept;
}
#endif
