#include <benchmark/benchmark.h>
#include <random>
#include <algorithm>

constexpr const int N = 1 << 29;
unsigned *A, *B;

int foo(unsigned *A, unsigned *B, int n) {
    unsigned sum = 0;
    for (unsigned i = 0; i < n; ++i)
        sum += A[i] * B[i];
    return sum;
}
void BM_foo(benchmark::State &state) {
    for(auto _: state)
        benchmark::DoNotOptimize(foo(A, B, state.range(0)));
}
BENCHMARK(BM_foo)->Range(1, 1 << 28);

int main(int argc, char** argv) {
    benchmark::Initialize(&argc, argv);
    if (benchmark::ReportUnrecognizedArguments(argc, argv))
        return 1;

    // Initialize A, B.
    {
        A = new unsigned[N];
        B = new unsigned[N];

        std::minstd_rand generator{};
        for(int i{0}; i != N; ++i) {
            A[i] = static_cast<unsigned>(generator());
            B[i] = static_cast<unsigned>(generator());
        }
    }

    benchmark::RunSpecifiedBenchmarks();

    delete [] A;
    delete [] B;
}
