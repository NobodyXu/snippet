#include <cstdio>
#include <utility>
struct A {
    A() = default;
    A(const A &a) noexcept {
        std::printf(__PRETTY_FUNCTION__);
    }
    A(A &&a) noexcept {
        std::printf(__PRETTY_FUNCTION__);
    }
};
int main() {
    const A a{};
    A a0{std::move(a)};
}
