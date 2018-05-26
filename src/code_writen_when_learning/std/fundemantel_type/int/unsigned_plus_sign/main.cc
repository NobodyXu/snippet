#include <iostream>
#include <typeinfo>
int main() {
    int i{-11};
    unsigned ui{10};

    auto result = i + ui;
    std::cout << result << std::endl
              << "typeid(result) = " << typeid(decltype(result)).name() << std::endl
              << "typeid(i) = " << typeid(decltype(i)).name() << std::endl
              << "typeid(ui) = " << typeid(decltype(ui)).name() << std::endl;
}
