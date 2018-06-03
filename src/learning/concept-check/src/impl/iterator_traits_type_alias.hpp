#ifndef __concept_check_impl_iterator_traits_type_alias_HPP__
#define __concept_check_impl_iterator_traits_type_alias_HPP__ value
# include <iterator>
namespace concept_check {
template <class T>
using It_tag    = typename std::iterator_traits<T>::iterator_category;
template <class T>
using It_val    = typename std::iterator_traits<T>::value_type;
template <class T>
using It_ref    = typename std::iterator_traits<T>::reference;
template <class T>
using It_ptr    = typename std::iterator_traits<T>::pointer;
template <class T>
using It_diff_t = typename std::iterator_traits<T>::difference_type;
}
#endif
