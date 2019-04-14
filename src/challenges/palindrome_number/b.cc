// 32ms, 8.1MB
#include <array>

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0)
            return false;
    
        // The decimal representation of an int has at most 10 digits
        std::array<char, 10> digits;
        
        auto last = 0;
        do {
            digits[last] = static_cast<char>(x % 10);
            x /= 10, ++last;
        } while(x != 0);
        
        --last;
        decltype(last) first = 0;
        while (first < last) {
            if (digits[first] != digits[last])
                return false;
            ++first, --last;
        }
        
        return true;
    }
};
