// 44ms,10.5MB
#include <vector>

class Solution {
public:
    bool isPalindrome(int x) {
        std::vector<char> digits;
        
        if (x < 0)
            return false;
        
        do {
            digits.emplace_back(static_cast<char>(x % 10));
            x /= 10;
        } while(x != 0);
        
        auto last = digits.size() - 1;
        decltype(last) first = 0;
        while (first < last) {
            if (digits[first] != digits[last])
                return false;
            ++first, --last;
        }
        
        return true;
    }
};
