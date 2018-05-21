#include <iostream>
#include <string_view>

int main() {
    auto max_size = std::string_view{}.max_size() / (1024 * 1024 * 1024);
    std::cout << std::boolalpha << (max_size < std::string_view::npos) << std::endl;
}
