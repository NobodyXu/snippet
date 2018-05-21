#include <iostream>
struct A {
    void Foo() { std::cout << "A" << std::endl; }
};
struct B :A {
    void Bar() { Foo(); }
};
int main() { B{}.Bar(); }
