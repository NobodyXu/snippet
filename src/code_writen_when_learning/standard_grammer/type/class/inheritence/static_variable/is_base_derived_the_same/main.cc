#include <iostream>
struct B {
    static int i;
};
int B::i = 10;
struct D: B {
    static void Foo() noexcept { i = 100; }
};
int main() {
    std::cout << "B::i: " << B::i << std::endl << "D::i " << D::i << std::endl;
    D::Foo();
    std::cout << "B::i: " << B::i << std::endl << "D::i " << D::i << std::endl;
}
