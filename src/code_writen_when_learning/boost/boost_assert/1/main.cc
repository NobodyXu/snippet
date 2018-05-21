#define BOOST_DISABLE_ASSERTS
#include "1.hpp"
#undef BOOST_DISABLE_ASSERTS
#include "2.hpp"
int main() {
    A::F();
    B::F();
}
