#ifndef  __twoSum_findtwoSum_HPP__
# define __twoSum_findtwoSum_HPP__

# include <iostream>
# include <vector>
# include <algorithm>
# include <utility>
# include <functional>

# include <thread>
# include <atomic>
# include <future>

using std::vector;
class Solution
{
private:
    using val_t = std::pair<int, int>;
    using Container = vector<val_t>;
    using It = typename Container::iterator;
    using size_t = typename Container::size_type;
    
    static bool cmp(const val_t &x, const val_t &y) noexcept
    {
        return x.first < y.first;
    }
       
    // Precondition: data.size() == 0, nums.size() != 0
    static void make_data(Container &data, const vector<int> &nums)
    {
        data.reserve(nums.size());

        int i = 0;
        for (auto &each: nums)
            data.emplace_back(each, i++);
        
        std::sort(data.begin(), data.end(), &cmp);
    }
    
    // launch_threads will launch threads in parallel.
    // It will call F with an int(thread id for accessing data) and std::forward<Args>(args)...
    template <class F>
    static void launch_threads(std::reference_wrapper<vector<std::thread>> pool, int thread_cnt, F &&f)
    {
        auto launch_other_threads = [=, f = std::forward<F>(f)]()
        {
            // This is thread 0!
            for (int i = 1; i != thread_cnt; ++i)
                pool.get().emplace_back(f, i);
        
            return std::invoke(f, 0);
        };
        
        pool.get().reserve(thread_cnt);
        pool.get().emplace_back(launch_other_threads);
    }
    
    // number of threads this process will ever have(including the main thread)
    int total_threads;
    // Thread pool and how much data each will process
    vector<std::thread> pool;
    size_t n;
    
    // The data for processing
    int target;
    Container data;
    // is_ready indicates whether the data is ready
    std::shared_future<void> is_ready;
    
    // Where result will be put. 
    // Since there is only one result, no atomic variable is needed
    vector<int> ret;
    // Synchronization of the event to terminate other running threads
    std::atomic_bool finished;
    
    void findtwoSum_impl(int thread_id, It beg, It end) noexcept
    {
        for (; beg != end && !finished.load(std::memory_order_acquire); ++beg) {
            int val = target - beg->first;
            auto it = std::lower_bound(data.begin(), data.end(), val_t{val, 0}, &cmp);
            
            if (it != data.end() && it->first == val &&
                (it->second != beg->second || (++it)->first == val)) {
                
                finished.store(true, std::memory_order_release);
                ret = {beg->second, it->second};
                break;
            }
        }
    }
    
    void findtwoSum(int thread_id) noexcept
    {
        std::shared_future<void>{is_ready}.wait();
        
        // Calculate the data that this thread will process
        auto beg = data.begin() + n * thread_id;
        auto end = beg + n;
               
        return findtwoSum_impl(thread_id, beg, end);
    }
    
    // thread_cnt must > 0
    void launch_threads_and_prepare_data(const vector<int> &nums, int thread_cnt)
    {
        // Initial the notification mechanism
        std::promise<void> promise;
        is_ready = promise.get_future().share();
        
        // Launch threads
        launch_threads(pool, thread_cnt, [this](int id) noexcept {
            return findtwoSum(id);
        });
        
        // Prepare data
        make_data(data, nums);
        
        n = data.size() / total_threads;
        
        // Notify threads that the data is ready
        promise.set_value();
    }
    
    // do_last_thread_cleanup process the remaining data and join threads
    void do_last_thread_cleanup()
    {
        // The main thred is the last thread.
        int thread_id = total_threads - 1;
        
        // findtwoSum_impl returns if any thread find the result.
        findtwoSum_impl(thread_id, data.begin() + n * thread_id, data.end());
        
        // Wait for other threads to finish.
        /*
        for (auto &thread: pool) {
            thread.join();
            std::cerr << " 1" << thread.get_id() << " is joinable? " << thread.joinable() << std::endl;
        }*/
        for (auto &thread: pool)
            if (thread.joinable())
                thread.join();
        for (auto &thread: pool)
            std::cerr << thread.get_id() << " is joinable? " << thread.joinable() << std::endl;

        // Clear containers
        pool.clear();
        data.clear();
    }
    
public:
    vector<int> twoSum(const vector<int> &nums, int target)
    {
        // Initialize class variables
        // I know that total_threads should be much lower depending on the size of input
        total_threads = std::thread::hardware_concurrency();
        if (total_threads < 2)
            total_threads = 2;

        this->target = target;
        ret.reserve(2);
        finished.store(false, std::memory_order_release);
        
        // Initialize class variable pool, n, data and is_ready
        launch_threads_and_prepare_data(nums, total_threads - 1);
        
        do_last_thread_cleanup();
        
        return std::move(ret);
    }
};

#endif
