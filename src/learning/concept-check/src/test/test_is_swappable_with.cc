#include <iostream>
#include <type_traits>
#include "is_swappable_with.hpp"
using namespace concept_check;
#define _OUTPUT(...)    "\n" #__VA_ARGS__ "\n\n"\
                        << "is_swappable: " << is_swappable_with_v< __VA_ARGS__ > << std::endl\
                        << "is_nothrow_swappable: " << is_nothrow_swappable_with_v< __VA_ARGS__ > << std::endl
#define OUTPUT(type) _OUTPUT(type &)
#define OUTPUT_FUNDEMENTAL_INT(type) OUTPUT(unsigned type) << OUTPUT(signed type) << OUTPUT(type *) << "\n"
template <char choice>
struct A {
    A() = default;
    A(const A&, std::enable_if_t<choice & 8>* = nullptr) {}
    A(A&&, std::enable_if_t<choice & 2>* = nullptr) {}
    auto operator = (const A&) -> std::enable_if_t<choice & 4, A&> {}
    auto operator = (A&&) -> std::enable_if_t<choice & 1, A&> {}
};
struct NoCPMV {
    NoCPMV(const NoCPMV&) = delete;
    NoCPMV(NoCPMV&&) = delete;
    NoCPMV& operator = (const NoCPMV&) = delete;
    NoCPMV& operator = (NoCPMV&&) = delete;
};
struct CANTHROW {
    CANTHROW(const CANTHROW&) noexcept(0) {}
    CANTHROW(CANTHROW&&) noexcept(0) {}
    CANTHROW& operator = (const CANTHROW&) noexcept(0) { return *this; }
    CANTHROW& operator = (CANTHROW&&) noexcept(0) { return *this; }
};
int main() {
    std::cout << std::boolalpha

              << OUTPUT(bool) << "\n"
              << OUTPUT_FUNDEMENTAL_INT(char)
              << OUTPUT(char16_t) << "\n"
              << OUTPUT(char32_t) << "\n"
              << OUTPUT_FUNDEMENTAL_INT(short)
              << OUTPUT_FUNDEMENTAL_INT(int)
              << OUTPUT_FUNDEMENTAL_INT(long)
              << OUTPUT_FUNDEMENTAL_INT(long long)
              << OUTPUT(float) << "\n"
              << OUTPUT(double) << "\n"
              << OUTPUT(NoCPMV) << "\n"
              << OUTPUT(CANTHROW);
}
