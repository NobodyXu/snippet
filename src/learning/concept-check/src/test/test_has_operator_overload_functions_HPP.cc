#include <iostream>
#include "has_operator_overload_functions.hpp"
using namespace concept_check;
struct A {
    A& operator ++ ();
    A operator ++ (int);
};
struct A_X {
    A_X(const A_X&) = delete;
    A_X(A_X&&) = delete;
    A_X& operator ++ ();
    A_X operator ++ (int);
};
struct B {
    B& operator ++ ();
};
struct C {
    C operator ++ (int);
};
struct D {
    int operator * ();
};
struct E {};
struct F {
    bool operator == (const F&);
};
struct G {
    bool operator != (const G&);
};
struct H {
    bool operator == (const H&);
    bool operator != (const H&);
};
#define OUTPUT_INC(type) "\n" #type "\n" << is_pre_incrementable_v< type &> << std::endl\
                                         << is_post_incrementable_v< type &> << std::endl
#define OUTPUT_DEREF(type) "\n" #type ": " << has_dereferenceable_v< type > << std::endl
#define OUTPUT_EQUALITYCOMP(type) "EqualityComparable: " << is_EqualityComparable_v< type > << std::endl
#define OUTPUT_INEQUALITYCOMP(type) "inEqualityComparable: " << is_inEqualityComparable_v< type > << std::endl
#define OUTPUT_COMP(type) "\n" #type "\n" << OUTPUT_EQUALITYCOMP(type) << OUTPUT_INEQUALITYCOMP(type)
int main() {
    std::cout << std::boolalpha

              << "incrementable"
              << OUTPUT_INC(int)
              << OUTPUT_INC(char)
              << OUTPUT_INC(float)
              << OUTPUT_INC(double)
              << OUTPUT_INC(char*)
              << OUTPUT_INC(void*)
              << OUTPUT_INC(void**)
              << OUTPUT_INC(A)
              << OUTPUT_INC(A_X)
              << OUTPUT_INC(B)
              << OUTPUT_INC(C)
              << OUTPUT_INC(D)
              << OUTPUT_INC(E)

              << "\ndereferenceable"
              << OUTPUT_DEREF(int)
              << OUTPUT_DEREF(int*)
              << OUTPUT_DEREF(char*)
              << OUTPUT_DEREF(void*)
              << OUTPUT_DEREF(void**)
              << OUTPUT_DEREF(D)
              << OUTPUT_DEREF(E)

              << "\nEqualityComparable"
              << OUTPUT_COMP(int)
              << OUTPUT_COMP(int*)
              << OUTPUT_COMP(void*)
              << OUTPUT_COMP(char)
              << OUTPUT_COMP(E)
              << OUTPUT_COMP(F)
              << OUTPUT_COMP(G)
              << OUTPUT_COMP(H);
}
