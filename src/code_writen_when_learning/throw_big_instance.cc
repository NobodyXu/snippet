#include <iostream>
#include <cstddef>
#include <algorithm>
#include <exception>
template <std::size_t size>
struct A: std::exception {
    A() noexcept {}
    A(const char * const str) noexcept {
	char *dit{buf};
	for(const char *rit{str}; *rit != 0 && dit != buf + 1024; *dit++ = *rit++); 
    }
    char buf[size];
    const char* what() const noexcept { return buf; }
};
int main() { throw A<9999>{"Hello, World!\nsdfdfferfkenvkjnvljenbvkljweqnkjlfadnklvnkwdnvcndjcnkjcdnkjldnkvclnklfnfkljvnfklvnfsklnfdsklnfdsklnvfnfvknfdsvklnvklnvfdfvsnnnnnnkjsddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd"}; }
