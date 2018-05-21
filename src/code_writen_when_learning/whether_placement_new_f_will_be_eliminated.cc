#include <new>
struct A {
    A(int i, char c) noexcept : _i(i), _c(c) {}
    int _i;
    char _c;
};
A* produceA(char *ptr, int i, char c) noexcept {
    return new (ptr) A{i, c};
}
