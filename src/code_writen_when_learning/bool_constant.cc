#include <iostream>
#include <type_traits>
int main() {
    std::cout << std::boolalpha
	      << std::bool_constant<1>{}
	      << std::bool_constant<0>{}
	      << std::endl;
}
