#include <iostream>
struct Foo { void F() {} };
int main() { std::cout << &Foo::F; }
