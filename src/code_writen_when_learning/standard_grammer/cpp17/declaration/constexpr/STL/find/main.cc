#include <algorithm>
int main() {
    constexpr const auto str = "aaaabccd";
    auto pos = std::find(str, str + 8, 'b');
    static_assert(pos == str + 4);
}
