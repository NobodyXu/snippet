#include "concepts/type_properties/operations/is_convertible_v.hpp"
using nxwheels::concept_check::is_implicitly_convertible_v;

struct B {};
struct D: B {};
struct pD: private B {};

int main() {
    static_assert(is_implicitly_convertible_v<D, B>);
    static_assert(is_implicitly_convertible_v<pD, B>);
}
