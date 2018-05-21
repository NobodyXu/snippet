#include <iostream>
struct A {
    int a;
    int b;
};
struct B {
    A a;
    A b;
};
std::ostream& operator << (std::ostream &os, const A &a)  { return os << a.a << " " << a.b; }
std::ostream& operator << (std::ostream &os, const B &b)  { return os << b.a << " " << b.b; }
int main() {
    B b{11, 23};
    std::cout << b << std::endl;
}
