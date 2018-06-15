#include <iostream>

struct Foo {
    int i;

    constexpr auto& operator ++ () noexcept {
	++i;
	return *this;
    }
};

template <int i>
void f() {
    std::cout << "i = " << i << std::endl;
}

template <class T> using as = T;

int main() {
    constexpr int i = 10;
    f<i>();

    constexpr Foo foo{2333};
    f<foo.i>();
}
