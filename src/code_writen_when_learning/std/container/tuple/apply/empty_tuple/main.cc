#include <tuple>
void F() {}
int main() {
    std::tuple<> tuple{};
    std::apply(&F, tuple);
}
