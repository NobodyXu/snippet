#include <vector>
#include <algorithm>
#include <utility>
#include <functional>

#include <thread>
#include <atomic>
#include <future>

using std::vector;

class Solution
{
    using val_t = std::pair<int, int>;
    using Container = vector<val_t>;
    using It = typename Container::iterator;
    using size_t = typename Container::size_type;
    
    static bool cmp(const val_t &x, const val_t &y) noexcept
    {
        return x.first < y.first;
    }
       
    static auto make_data(const vector<int> &nums)
    {
        Container vec(nums.size());
        int i = 0;        

        for (auto &each: vec) {
            each.first = nums[i];
            each.second = i++;
        }
        
        std::sort(vec.begin(), vec.end(), &cmp);
        
        return vec;
    }
    
    // launch_threads will launch threads in parallel.
    // It will call F with an int(thread id for accessing data) and std::forward<Args>(args)...
    template <class F, class First, class ...Args>
    static void launch_threads(vector<std::thread> &pool, int thread_cnt, F &&f, First &&first, Args &&...args)
    {
        auto launch_other_threads = [&]()
        {
            // This is thread 0!
            for (int i = 1; i != thread_cnt; ++i)
                pool.push_back(std::thread{std::forward<F>(f), 
                                           std::forward<First>(first), i, std::forward<Args>(args)...});
        
            std::invoke(std::forward<F>(f), std::forward<First>(first), 0, std::forward<Args>(args)...);
        };
        
        pool.reserve(thread_cnt);
        pool.push_back(std::thread{launch_other_threads});
    }
    
    // number of threads this process will ever have(include the main thread)
    int total_threads;
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
    std::atomic_bool finished{false};
    
    void findtwoSum_impl(int thread_id, It beg, It end) noexcept
    {
        for (; beg != end && !finished.load(std::memory_order_release); ++beg) {
            int val = target - beg->first;
            auto it = std::lower_bound(data.begin(), data.end(), val_t{val, 0}, &cmp);
            
            if (it != data.end() && it->first == val &&
                (it->second != beg->second || (++it)->first == val)) {
                
                ret = {beg->second, it->second};
                finished.store(true, std::memory_order_release);
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
               
        findtwoSum_impl(thread_id, beg, end);
    }
    
    // thread_cnt must > 0
    void launch_threads_and_prepare_data(const vector<int> &nums, int thread_cnt)
    {
        // Initial the notification mechanism
        std::promise<void> promise;
        is_ready = promise.get_future().share();
        
        // Launch threads
        launch_threads(pool, thread_cnt, &Solution::findtwoSum, this);
        
        // Prepare data
        data = make_data(nums);
        
        n = (data.end() - data.begin()) / total_threads;
        
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
        for (auto &thread: pool)
            thread.join();
    }
    
public:
    vector<int> twoSum(const vector<int> &nums, int target)
    {
        total_threads = std::thread::hardware_concurrency();
        if (total_threads < 2)
            total_threads = 2;
        this->target = target;
        
        launch_threads_and_prepare_data(nums, total_threads - 1);
        
        do_last_thread_cleanup();
        
        return ret;
    }
};
