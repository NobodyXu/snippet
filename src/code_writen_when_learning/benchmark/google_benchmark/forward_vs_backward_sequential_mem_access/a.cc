#include <benchmark/benchmark.h>
#include <vector>
#include <utility>
#include <container_and_algorithm/range/range.hpp>

template <class T = char>
auto get_vector(benchmark::State &state) noexcept
{
    std::vector<T> ret;

    try {
	ret.resize(state.range(0));
    } catch(const std::bad_alloc&) {
	state.SkipWithError("Memory allocation fails");
    }

    state.SetComplexityN(state.range(0));
    return ret;
}

void BM_forward(benchmark::State& state) noexcept
{
    auto v = get_vector(state);

    for (auto &&_: state)
        for (auto &each: v) {
	    benchmark::DoNotOptimize(each);
	    benchmark::ClobberMemory();
	}
}

void BM_backward(benchmark::State &state) noexcept
{
    auto v = get_vector(state);

    for (auto &&_: state)
	for (auto &each: nxwheels::range{std::make_reverse_iterator(v.end()), std::make_reverse_iterator(v.begin())}) {
	    benchmark::DoNotOptimize(each);
	    benchmark::ClobberMemory();
	}
}

#define Config() RangeMultiplier(2)->Range(8, 1 << 30)->Complexity();

BENCHMARK(BM_forward)->Config();
BENCHMARK(BM_backward)->Config();

BENCHMARK_MAIN();
