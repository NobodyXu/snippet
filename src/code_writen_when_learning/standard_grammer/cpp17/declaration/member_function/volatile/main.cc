#include <type_traits>

struct A {
    void F() volatile {
        static_assert(std::is_volatile<decltype(*this)>{}());
    }
};

int main() {}
