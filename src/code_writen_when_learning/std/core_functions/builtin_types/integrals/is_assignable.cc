#include <utility>
int main() {
    using type = decltype(std::declval<int&>() = std::declval<int>());
}
