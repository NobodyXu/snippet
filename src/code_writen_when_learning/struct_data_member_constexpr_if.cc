#include <iostream>
struct A {
    char b;
    void F() {
	if constexpr(b == 0) std::cout << "wee\n";
    }
};
int main() {
    A{0}.F();
    A{1}.F();
}
