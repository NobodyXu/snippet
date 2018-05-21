#include <iostream>
[[gnu::always_inline]]void f();
//[[gnu::always_inline]]void f() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
void f() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
int main() { f(); }
