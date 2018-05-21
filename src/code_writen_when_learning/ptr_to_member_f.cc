#include <iostream>
#include <utility>
#include <algorithm>
#include <cstddef>
struct Base {
    int i;
    void A() {}
    virtual void B() {}
};
struct Derived: Base { void B() {} };
struct VirtuallyDerived: virtual Base { void B() {} };

template <class T> struct Wrapper { T obj; };
template <class T> Wrapper(T) -> Wrapper<T>;
std::basic_ostream<char>& operator<<(std::basic_ostream<char> &s, std::pair<void**, void**> p) {
    std::for_each(p.first, p.second, [&s](void * const &x){ s << x << ", "; }); 
    return s;
}
template <class T>
std::basic_ostream<char>& operator<<(std::basic_ostream<char> &s, Wrapper<T> w) {
    const std::size_t size = sizeof(T) / sizeof(void*);
    auto p = static_cast<void**>(static_cast<void*>(&w));
    return s << "size = " << size << ", Content: " << std::pair{p, p + size} << ".\n";
}
int main() {
    std::cout << Wrapper{&Base::A}
	      << Wrapper{&Derived::A}
	      << Wrapper{&Base::B}
	      << Wrapper{&Derived::B}
	      << Wrapper{&VirtuallyDerived::B};
}
