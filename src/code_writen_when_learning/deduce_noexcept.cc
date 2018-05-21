#include <type_traits>
template <class F, bool is_noexcept = 0> struct D;
template <class _Ret, class ..._Args, bool _is_noexcept>
struct D<_Ret (*)(_Args...), _is_noexcept> {
    typedef _Ret  Ret;
    static inline const constexpr bool is_noexcept{_is_noexcept};
};
template <class Ret, class ...Args>
struct D<Ret (*)(Args...) noexcept, 0>: D<Ret (*)(Args...), 1> {};
template <class F, bool expect_is_noexcept>
void Test() noexcept {
    typedef D<int (*)() noexcept(0)> d1;
    typename d1::Ret{1111};
    static_assert(d1::is_noexcept == expect_is_noexcept);
}
int main() {
    static_assert(std::is_same<int (*)(), int (*)() noexcept>{}());

    Test<int (*)(), 0>();
    Test<int (*)() noexcept, 1>();
}
