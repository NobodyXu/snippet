#include <functional>
template <class> struct traits {};
template <class T, class Cmp = std::less<>, class = traits<T>> 
struct Foo {
    T a;
    Cmp c{};
};
template <class T, class Cmp> Foo(T, Cmp) -> Foo<T, Cmp>;
template <class T> Foo(T) -> Foo<T>;
int main() {
    Foo f{1};
    Foo f2{1, std::less<int>{}};
}
