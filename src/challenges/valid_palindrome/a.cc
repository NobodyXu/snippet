#include <string>

class Solution {
    static bool is_alnum(char c) noexcept
    {
        return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
    }
    
    // This assumes is_alpha(c) == true
    static char lower(char c) noexcept
    {
        return (c >= 'A' && c <= 'Z') ? c - ('A' - 'a') : c;
    }
public:
    bool isPalindrome(std::string &s) {
        if (!s.empty()) {
            auto last = &s[s.size() - 1];
            auto first = &s[0];
            
            while (first < last) {
                if (!is_alnum(*first)) {
                    ++first;
                } else if (!is_alnum(*last)) {
                    --last;
                } else if (lower(*first) != lower(*last)) {
                    return false;
                } else
                    ++first, --last;
            }
        }
        
        return true;
    }
};
