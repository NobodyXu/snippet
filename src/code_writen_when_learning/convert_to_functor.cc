#include <iostream>
#define MSG() __PRETTY_FUNCTION__
typedef const char* cstr_t;
struct A { cstr_t operator () (void) { return MSG(); } };
struct B { operator A() { return {}; } };
int main() {
    std::cout << B{}();
}
