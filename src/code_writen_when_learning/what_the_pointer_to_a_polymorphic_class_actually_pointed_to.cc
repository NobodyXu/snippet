#include <iostream>
struct A {
    virtual void F() {}
    int i;
    A(int I): i{I} {}
};
int main() {
    A a(1000);
    std::cout << &a << " " << *static_cast<int*>(static_cast<void*>(static_cast<void**>(static_cast<void*>(&a)) + 1)) << std::endl;
}
