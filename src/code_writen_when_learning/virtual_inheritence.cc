#define DEF_V(NAME) virtual const char* NAME () { return __PRETTY_FUNCTION__; }
struct Empty {};
struct B1 { int i; };
struct B2 { DEF_V(F) };
struct D1: virtual Empty, virtual B1 {} _D1{};
struct D2: virtual Empty, virtual B2 {} _D2{};
struct D3: virtual Empty {} _D3{};
struct D4: virtual B2 {} _D4{};
int main() {}
