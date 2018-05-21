#include <iostream>
#include <cassert>
struct A {
    void f() { assert(0); }
};
int main() { A{}.f(); }
