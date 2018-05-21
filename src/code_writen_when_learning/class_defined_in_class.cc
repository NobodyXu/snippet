#include <iostream>
class A {
    int 
	integer;
public:
    A(int _int): integer(_int) {}
    struct B {
	A &a;
	operator int () const noexcept { return a.integer; }
    };
};
int main() { 
    A a{2333};
    A::B b{a};
    std::cout << static_cast<int>(b) << std::endl;
}
