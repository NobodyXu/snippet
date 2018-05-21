#include <iostream>
typedef const char* cstr;
struct A {
    virtual cstr F() { return __PRETTY_FUNCTION__; }
};
int main() {
    cstr (A::*mfptr)(void) = &A::F;
}
