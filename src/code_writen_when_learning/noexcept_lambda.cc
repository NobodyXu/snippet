#include <iostream>
auto F = [](){};
int main() {
    std::cout << std::boolalpha
	      << "noexcept(F()):" << noexcept(F()) << ".\n";
}
