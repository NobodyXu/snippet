#include <iostream>
#include <deque>
#include <cstdint>

template <class T> struct Wrapper {};

template <class T>
std::ostream& operator << (std::ostream &in, Wrapper<T>) {
    return in << sizeof(std::deque<T>) << std::endl;
}
int main() {
    std::cout << Wrapper<char>{}
	      << Wrapper<char16_t>{}
	      << Wrapper<char32_t>{}
	      << Wrapper<std::int64_t>{};
}
