#include <cstdio>
template <class T, const T v>
struct A {
    inline static constexpr const auto value = v;
    constexpr T operator () (void) const noexcept { return value; }
};
int main() { printf("%d\n", A<int, 1>{}()); }
