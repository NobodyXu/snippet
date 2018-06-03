#include <iostream>
#include "../impl/macro/define_CONCEPT_T.hpp"
CONCEPT_T a = 1;
CONCEPT_T F() { return 0; }
namespace Foo {
DEF_CONCEPT_1(TEST1, 1, DEF_CONCEPT_F)
DEF_CONCEPT_1(TEST1_V, 1, DEF_CONCEPT_V);
DEF_CONCEPT_1(TEST1_T, 1, DEF_CONCEPT_T);
}
namespace Bar {
using Foo::TEST1;
DEF_CONCEPT_1(TEST1, , DEF_CONCEPT_V_WRAPPER_FOR_F);
DEF_CONCEPT_1(TEST1, , DEF_CONCEPT_T_WRAPPER_FOR_F);
} /* Bar */
#define OUTPUT(STH) STH << std::endl
int main() {
    std::cout << std::boolalpha
	            << OUTPUT(a)
	            << OUTPUT(F())
              << OUTPUT(Foo::TEST1_V<int>)
              << OUTPUT(Foo::TEST1_T<int>{}())
              << OUTPUT(Foo::TEST1<int>())
              << OUTPUT(Bar::TEST1_v<int>)
              << OUTPUT(Bar::TEST1_t<int>{}())
              << OUTPUT(Bar::TEST1<int>());
}
