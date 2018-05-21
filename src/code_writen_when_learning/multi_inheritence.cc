#define DEF_VF(NAME) virtual void NAME () {}
struct Empty {};
struct A {
    DEF_VF(F1)
    int i;
} _A{};
struct B {
    DEF_VF(F2)
    int _i;
} _B{};
struct C: A, B {
    DEF_VF(F1)
    DEF_VF(F2)
    DEF_VF(F3)
    int __i;
} _C{};
struct D: Empty, A {} _D{};
int main() {}
