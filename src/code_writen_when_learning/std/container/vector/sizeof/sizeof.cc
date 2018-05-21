#include <cstdint>
#include <iostream>
#include <vector>
#include <tuple>
template <class T, class ...Args>
void print() {
    std::cout << sizeof(std::vector<T>) << "\n";
    if constexpr(sizeof...(Args) > 0)
        print<Args...>();
}
int main() { print<int8_t, int16_t, int32_t, int64_t, char[128], char[256]>(); }
