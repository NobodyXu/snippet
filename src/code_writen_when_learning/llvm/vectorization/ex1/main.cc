#include <benchmark/benchmark.h>
#include <random>
#include <algorithm>

constexpr const int N = 1 << 29;
int *A, *B;

int foo(int *A, int *B, int n) {
    unsigned sum = 0;
    for (int i = 0; i < n; ++i)
        if (A[i] > B[i])
            sum += A[i] + 5;
    return sum;
}
void BM_foo(benchmark::State &state) {
    for(auto _: state)
        benchmark::DoNotOptimize(foo(A, B, state.range(0)));
}
BENCHMARK(BM_foo)->Range(1, 1 << 28);

int main(int argc, char** argv) {
    benchmark::Initialize(&argc, argv);
    if (::benchmark::ReportUnrecognizedArguments(argc, argv))
        return 1;

    // Initialize A, B.
    {
        A = new int[N];
        B = new int[N];

        std::minstd_rand generator{};
        for(int i{0}; i != N; ++i) {
            A[i] = static_cast<int>(generator());
            B[i] = static_cast<int>(generator());
        }
    }

    benchmark::RunSpecifiedBenchmarks();

    delete [] A;
    delete [] B;
}
