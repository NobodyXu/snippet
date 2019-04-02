#include <iostream>
#include <sstream>
#include <chrono>

#include <vector>
#include <thread>
#include <future>

using namespace std::chrono_literals;

static const auto total_threads = 8;
constexpr static const auto sleep_for_v = 10s;

using Clock_t = std::chrono::high_resolution_clock;
using time_point = typename Clock_t::time_point;
using rep = typename Clock_t::rep;

using result_container_t = std::vector<rep>;
using result_It = typename result_container_t::iterator;

void print(std::shared_future<void> future, const time_point *tp1_p, result_It it)
{
    try {
        std::ostringstream ss;
        future.wait();
        auto time = (Clock_t::now() - *tp1_p).count();
    
        ss << "In thread " << std::this_thread::get_id()
           << ", it takes " << time
           << " ns for future.wait() to return after the promise is set."
           << std::endl << std::flush;

        std::cerr << ss.str() << std::flush;

        *it = time;
    } catch(...) {
        std::ostringstream ss;

        ss << "In thread " << std::this_thread::get_id() << " an exception is thrown."
           << std::endl << std::flush;

        std::cerr << ss.str() << std::flush;
        throw;
    }
}

int main()
{
    std::vector<std::thread> pool;
    pool.reserve(total_threads);

    std::vector<rep> bench_result(total_threads);

    using size_t = typename decltype(pool)::size_type;

    {
        std::promise<void> p;
        auto future = p.get_future().share();
        time_point tp;

        size_t i = 0;
        try {
            for (; i != total_threads; ++i)
                pool.emplace_back(&print, future, &tp, bench_result.begin() + i);
        } catch(const std::system_error &e) {
            std::cerr << "The creation of the " << i + 1 << "thread fails." << std::endl << std::flush;
            throw;
        }

        std::cerr << "Finish creating threads." << std::endl
                  << "Now sleep for " << sleep_for_v.count() 
                  << "s before calling p.set_value() so that the threads are all created." 
                  << std::endl << std::flush;
                  
        std::this_thread::sleep_for(sleep_for_v);

        tp = Clock_t::now();
        p.set_value();
    }

    try {
        for (auto &thread :pool)
            thread.join();
    } catch(...) {
        std::cerr << "The main thread thorws!\n" << std::flush;
        throw;
    }

    rep sum = 0;
    for (auto &each: bench_result)
        sum += each;
    std::cerr << "Averge time for future.wait() to return after the promise is set is " 
              << sum / bench_result.size() << std::endl;

    return 0;
}
