#include <benchmark/benchmark.h>
#include <thread>
#include <vector>

void f()
{}

static void BM_thread(benchmark::State &state)
{
    for (auto &&_: state) {
        std::vector<std::thread> v;

        for (int i = 0; i != 8; ++i)
            v.push_back(std::thread{f});

        for (auto &each: v)
            each.join();
    }
}

BENCHMARK(BM_thread);

BENCHMARK_MAIN();
