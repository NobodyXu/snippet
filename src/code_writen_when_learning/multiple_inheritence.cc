#include <iostream>
struct auto_start_newline {
    const char *ptr;
};
std::basic_ostream<char>& operator<<(std::basic_ostream<char> &s, auto_start_newline str_w) { return s << str_w.ptr << std::endl; }
#define DEF_VF(NAME) virtual auto_start_newline NAME () const noexcept { return {__PRETTY_FUNCTION__}; }

struct A {
    DEF_VF(F1)
};
struct B {
    DEF_VF(F2)
};
struct C: A, B {
    DEF_VF(F1)
    DEF_VF(F2)
    DEF_VF(F3)
};
int main() {
    C c;
    A *pa = &c;
    B *pb = &c;
    C *pc = &c;

    using mfptr = auto_start_newline (*)(void*);
    mfptr *vtableA = static_cast<mfptr*>(static_cast<void*>(pc));
    mfptr *vtableB = static_cast<mfptr*>(static_cast<void*>(pc)) + 1;
    std::cout 
	      << "sizeof(C) = " << sizeof(C) << std::endl
	      << pa->F1()
	      << pb->F2()
	      << pc->F1()
	      << pc->F2()
	      << pc->F3()
	      
	      << vtableA[0](pc);
}
