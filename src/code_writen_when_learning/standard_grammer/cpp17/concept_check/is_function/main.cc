#include <type_traits>

template <class T> struct is_function: std::false_type {};
template <class Ret, class ...Args> struct is_function<Ret (Args...)>: std::true_type {};
template <class T>
constexpr const static inline bool is_function_v = is_function< std::remove_cv_t< std::remove_reference_t<T> > >::value;
int main() {
    static_assert(!is_function_v<int>);
    static_assert(is_function_v<int()>);
    static_assert(is_function_v<int() const>);
    static_assert(is_function_v<int() const volatile>);
    static_assert(is_function_v<int() const volatile &&>);
}
