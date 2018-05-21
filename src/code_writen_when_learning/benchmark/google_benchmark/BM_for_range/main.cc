#include <benchmark/benchmark.h>
#include <vector>

auto get_vector(int size) {
    return std::vector<int>(size, 2333);
}
template <class F>
void BM_for_range(benchmark::State &state)
{
    for(auto _: state) {
        state.PauseTiming();

        F{}(get_vector(state.range(0)), state);//Run the test
    }
}
struct v1 {
    template <class T>
    void operator () (std::vector<T> v, benchmark::State &state) {
        state.ResumeTiming();

        auto size = v.size();
        decltype(size) i = 0;
        for (; i != size; i++) {
            v[i] *= v[i];
        }
    }
};
struct v2 {
    template <class T>
    void operator () (std::vector<T> v, benchmark::State &state) {
        state.ResumeTiming();

        for (int& val : v) {
            val *= val;
        }
    }
};

BENCHMARK_TEMPLATE(BM_for_range, v1)->Range(64, (1 << 30));
BENCHMARK_TEMPLATE(BM_for_range, v2)->Range(64, (1 << 30));
BENCHMARK_MAIN();
