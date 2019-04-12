#include <vector>
#include <algorithm>
#include <utility>

using std::vector;

class Solution
{
    using val_t = std::pair<int, int>;
    using container = std::vector<std::pair<int, int>>;

    static bool cmp(const val_t &x, const val_t &y) noexcept
    {
        return x.first < y.first;
    }
       
    static auto make_vec(const std::vector<int> &nums)
    {
        container vec;
        int i = 0;
        
        vec.reserve(nums.size());
        for (auto &each: nums)
            vec.emplace_back(each, i++);
        
        return vec;
    }
    
public:
    vector<int> twoSum(const vector<int> &nums, int target)
    {
        auto vec = make_vec(nums);
        auto beg = vec.begin(), end = vec.end();
        
        std::sort(beg, end, cmp);
        
        auto it1 = beg;
        auto it2 = std::find_if(vec.begin(), vec.end(), [&, val = 0](auto &each) mutable noexcept {
            val = target - each.first;
            it1 = std::lower_bound(beg, end, val_t{val, 0}, cmp);
            
            return (it1 != end && it1->first == val) && (it1->second != each.second || (++it1)->first == val);
        });
        
        return {it1->second, it2->second};
    }
};
