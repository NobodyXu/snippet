#include <iostream>

int convert(char c) noexcept {
    return int{c};
}

int main() {
    char c;

    std::cout << +c << std::endl
              << int{c} << std::endl;
}
