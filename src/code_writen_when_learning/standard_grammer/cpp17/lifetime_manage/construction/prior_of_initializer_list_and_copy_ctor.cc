#include <iostream>
#include <initializer_list>
struct S {
    int i;
    char c;
    S() = default;
    S(const S&) = default;
    S(std::initializer_list<int>) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};
int main() {
    S s1 = S();
    S s2 = {s1};
}
