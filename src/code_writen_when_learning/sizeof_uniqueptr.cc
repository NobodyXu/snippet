#include <iostream>
#include <memory>
#include <cstdint>
#define _OUTPUT_sizeof(TYPE)		  \
    "sizeof(std::unique<" << #TYPE << ">):"\
    << sizeof(std::unique_ptr< TYPE >) << std::endl
#define OUTPUT_sizeof(TYPE) \
    _OUTPUT_sizeof(TYPE)    \
 << _OUTPUT_sizeof(TYPE [0])\
 << _OUTPUT_sizeof(TYPE [1])

struct empty {};
struct size_128 { char c[128]; };
int main() { 
    std::cout << OUTPUT_sizeof(char16_t)
	      << OUTPUT_sizeof(char32_t)
	      << OUTPUT_sizeof(std::uint8_t)
	      << OUTPUT_sizeof(std::uint16_t)
	      << OUTPUT_sizeof(std::uint32_t)
	      << OUTPUT_sizeof(std::uint64_t)
	      << OUTPUT_sizeof(empty)
	      << OUTPUT_sizeof(size_128);
}
