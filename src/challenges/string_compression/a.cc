#include <vector>
#include <algorithm>
#include <iterator>
#include <utility>

class Solution {
    template <class It, class T>
    auto count(It beg, It end, T val) noexcept
    {
        auto it = std::find_if(beg, end, [&val](auto &x) noexcept {
            return val != x;
        });
        return it - beg;
    }
    
    template <class It>
    void reverse(It beg, It last) noexcept
    {
        while (beg < last) {
            std::iter_swap(beg, last);
            
            ++beg, --last;
        }
    }
    
    // Precondition: [beg, end) is long enough
    template <class It, class T>
    auto itos(It beg, T val) noexcept
    {
        It it = beg;
        do {
            *it++ = static_cast<char>(val % 10 + '0');
            val /= 10;
        } while (val != 0);
        
        reverse(beg, it - 1);
        
        return it;
    }
    
public:
    int compress(std::vector<char>& chars) noexcept
    {
        auto beg = chars.begin(), end = chars.end(), out = beg;
        
        for (; beg != end; ) {
            auto cnt = count(beg, end, *beg);
            
            *out++ = *beg;
            if (cnt > 1)
                out = itos(out, cnt);
            beg += cnt;
        }
        
        return out - chars.begin();
    }
};
