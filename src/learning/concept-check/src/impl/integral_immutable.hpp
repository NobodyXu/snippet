#ifndef __concept_check_impl_integral_immutable_HPP__
# define __concept_check_impl_integral_immutable_HPP__
namespace concept_check {
template <class T, const T v>
struct integral_immutable {
    inline static constexpr const T value = v;
    typedef T value_type;
    typedef integral_immutable type; // using injected-class-name
    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator () (void) const noexcept { return value; }
};
template <const bool B> using bool_immutable = integral_immutable<bool, B>;
}
#endif
