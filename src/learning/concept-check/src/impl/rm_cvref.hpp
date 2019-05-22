#ifndef __concept_check_rm_cvref_HPP__
#define __concept_check_rm_cvref_HPP__
# include <type_traits>
namespace concept_check {
template <class T>
using rm_ref_t = std::remove_reference_t<T>;
template <class T>
using rm_cv_t = std::remove_cv_t<T>;
template <class T>
using rm_cvref_t = rm_ref_t<rm_cv_t<T>>;
}//concept_check
#endif
