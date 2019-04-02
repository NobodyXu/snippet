#include <vector>
#include <algorithm>
#include <utility>

using std::vector;

class Solution
{
    constexpr static inline const auto cmp = 
        [](const auto &x, const auto &y) noexcept {
        return x.first < y.first;
    };
       
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
        auto beg = vec.begin(), end = vec.end();
        
        std::sort(beg, end, cmp);
        
        int val;
        for (auto &each: vec) {
            val = target - each.first;
            auto it = std::lower_bound(beg, end, std::pair<int, int>{val, 0}, cmp);
            
            if (it != vec.end() && it->first == val) {
                // If they are the same element...
                if (it->second == each.second)
                    if ((++it)->first != val)
                        continue;
                
                return {each.second, it->second};
            }
        }
        
        return {};
    }
};
