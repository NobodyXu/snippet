#include <cstdio>
#include <cstdint>
#include "../bound.hpp"
#include <algorithm>
#include <random>
#include "Helpers_for_testing_algorithms.hpp"
using namespace sort;
struct rand_gen {
    std::default_random_engine engine;
    std::uniform_int_distribution<std::size_t> adaptor;
    rand_gen(const std::size_t &max) noexcept: adaptor(0, max) {}
    auto operator () (void) noexcept { return adaptor(engine); }
};
int main(const int argc, const char * const argv[]) {
    if(argc == 1) {
        fprintf(stderr, "Usage: %s [files]\n", argv[0]);
        return 1;
    }
    test::LoadFileIntoMem data{};
    std::for_each(argv + 1, argv + argc, [&data](const char * const filename) {
        data.ReLoad(test::open(filename, O_RDONLY));
        auto beg = static_cast<uint8_t*>(data.ptr);
        auto size = data.get_buf_size();
        rand_gen gen{size};
        auto &val = *(beg + gen());
        uint8_t *result_of_array;
        {
            auto ret1 = beg + 1;
            auto cnt = upper_bound{}(beg, ret1, beg + size, val);
            auto ret2 = std::upper_bound(beg, beg + size, val, std::less<>{});
            assert(ret1 == ret2);
        }
    });
}
