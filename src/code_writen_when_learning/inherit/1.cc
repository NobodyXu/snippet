#include <vector>
#include <type_traits>
template <class T, bool b = std::is_trivially_copy_constructible<T>{}()>
struct A {
    typedef T type;
};
template <class T>
struct A<T, 0>: A<T, 1> {
    typedef std::vector<T> vec_t;
    static constexpr const bool b = 0;
};
template <class T> using _T = typename A<T>::type;
template <class T> using vec_T = typename A<T>::vec_t;
int main() {
    _T<int>{};
    _T<std::vector<int>>{};
    vec_T<std::vector<int>>{};
}
