#include <cstdio>
#define _DEF(A, B) constexpr bool A () noexcept { return 1; }
#define DEF(A, B, C) template <class A> C(A, B)
DEF(Foo,, _DEF)
int main() { printf("%d\n", Foo<int>()); }
