#include <string>
#include <algorithm>

class Solution {
    // Precondition: ret.sie() >= other.size()
    auto& addBinary_inplace(std::string &ret, std::string &other)
    {
        auto first1 = other.begin(), last1 = other.end() - 1;
        auto first2 = ret.begin(), last2 = ret.end() - 1;
        char inc_bit = 0;
        
        while (first1 <= last1) {
            auto new_bit = (*last1 - '0') + (*last2 - '0') + inc_bit;
            
            inc_bit = (new_bit & 2) >> 1;
            *last2 = (new_bit & 1) + '0';
            
            --last1, --last2;
        }
        
        if (inc_bit) {
            while (first2 <= last2) {
                auto new_bit = *last2 + inc_bit;
            
                inc_bit = new_bit == '2';
                *last2 = inc_bit ? '0' : new_bit;
                
                --last2;
            }
            
            if (inc_bit)
                ret.insert(0, 1, '1');
        }
        
        return ret;
    }
    
public:
    auto& addBinary(std::string &a, std::string &b) {
        if (b.size() > a.size()) {
            return addBinary_inplace(b, a);
        } else {
            return addBinary_inplace(a, b);
        } 
    }
};
