#include <vector>
#include <algorithm>
#include <tuple>

using std::vector;

class Solution
{
    constexpr static inline const auto cmp = 
        [](const auto &x, const auto &y) noexcept {
        return x.first < y.first;
    };
    constexpr static inline const auto cmp2 = 
        [](const auto &x, const auto &y) noexcept {
        return x.first < y;
    };
    
    template <class F>
    static auto binary_search(const vector<std::pair<int, int>> &vec, int val, F f) noexcept
    {
        auto it = std::lower_bound(vec.begin(), vec.end(), val, f);
    
        if (it != vec.end() && it->first != val)
            it = vec.end();
        
        return it;
    }
    
    static auto make_vec(const vector<int> &nums)
    {
        vector<std::pair<int, int>> vec(nums.size());
        
        int i = 0;
        for (auto &each: vec) {
            each.first = nums[i];
            each.second = i++;
        }
        
        return vec;
    }
    
public:
    vector<int> twoSum(const vector<int> &nums, int target) {       
        auto vec = make_vec(nums);
        
        std::sort(vec.begin(), vec.end(), cmp);
        
        for (auto &each: vec) {
            auto it = binary_search(vec, target - each.first, cmp2);
            
            if (it != vec.end()) {
                // If they are the same element...
                if (it->second == each.second)
                    if ((++it)->first != each.first)
                        continue;
                
                return {each.second, it->second};
            }
        }
        
        return {};
    }
};
