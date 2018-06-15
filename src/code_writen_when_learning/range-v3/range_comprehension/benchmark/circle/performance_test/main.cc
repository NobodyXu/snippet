/*
 * Range v3 library
 *
 *  Copyright Eric Niebler 2013-present
 *
 *  Use, modification and distribution is subject to the
 *  Boost Software License, Version 1.0. (See accompanying
 *  file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt)
 *
 * Project home: https://github.com/ericniebler/range-v3
 *
 */
#include <range/v3/all.hpp>
#include <benchmark/benchmark.h>

using namespace ranges;

void BM_range_comprehension_method1(benchmark::State &state) {
    // Define an infinite range containing all the Pythagorean triples:
    auto triples = view::for_each(view::ints(1), [](int z)
    {
        return view::for_each(view::ints(1, z + 1), [=](int x)
        {
            return view::for_each(view::ints(x, z + 1), [=](int y)
            {
                return yield_if(x * x + y * y == z * z, std::make_tuple(x, y, z));
            });
        });
    });

    auto count = state.range(0);
    auto limited_triples = triples | view::take(count);
    for(auto _: state)
        for(auto result: limited_triples)
            benchmark::DoNotOptimize(result);
}
BENCHMARK(BM_range_comprehension_method1)->Range(1 << 4, 1 << 5);
void BM_c_style_method1(benchmark::State &state) {
    auto triples = [](auto max_triples)
    {
        for(int z = 1, found = 0; ; ++z)
            for(int x = 1; x <= z; ++x)
                for(int y = x; y <= z; ++y)
                    if(x * x + y * y == z * z) {
                        benchmark::DoNotOptimize(std::make_tuple(x, y, z));
                        if(++found > max_triples)
                            return;
                    }
    };

    auto count = state.range(0);
    for(auto _: state)
        triples(count);
}
BENCHMARK(BM_c_style_method1)->Range(1 << 4, 1 << 5);

void BM_range_comprehension_method2(benchmark::State &state) {
    // Define an infinite range containing all the Pythagorean triples:
    auto triples = view::for_each(view::ints(1), [](int z)
    {
        return view::for_each(view::ints(1, z + 1), [=](int x)
        {
            int y = z * z - x * x;
            return view::for_each(view::ints(x, z + 1), [=](int y)
            {
                return yield_if(x * x + y * y == z * z, std::make_tuple(x, y, z));
            });
        });
    });

    auto count = state.range(0);
    auto limited_triples = triples | view::take(count);
    for(auto _: state)
        for(auto result: limited_triples)
            benchmark::DoNotOptimize(result);
}

BENCHMARK_MAIN();
