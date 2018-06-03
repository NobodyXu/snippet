/*
 * Test for insert.sort.
 * Generate random data then sort them.
 * This file does not mean to test the speed of insert_sort, but the correctness of it.
 */
#include <iostream>
#include <cstdint>
#include <random>
#include <algorithm>
#include "binarysort.hpp"
auto generate_random_array(std::size_t num) noexcept {
    std::default_random_engine en;
    auto ret{new typename std::default_random_engine::result_type[num]};
    std::for_each(ret, ret + num, [&](auto &ele){ ele = en(); });
    return ret;
}
int main() {
    constexpr const std::size_t size{1 << 5};
    auto array = generate_random_array(size);
    sort::binarysort(array, array + 1, array + size);
}
