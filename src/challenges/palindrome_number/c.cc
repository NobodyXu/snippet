#include <array>

class Solution {
    // The follwoing function is adapted from
    //https://www.geeksforgeeks.org/number-of-leading-zeros-in-binary-representation-of-a-given-number/
    static int largest_ratio(int x) noexcept
    {
        int ratio = 1;
        int tmp;
        
        tmp = x / 100000; if (tmp != 0) { ratio *= 100000; x = tmp; }
        tmp = x / 100;  if (tmp != 0) { ratio *= 100; x = tmp; }
        tmp = x / 10;   if (tmp != 0) { ratio *= 10; x = tmp;
        tmp = x / 10;   if (tmp != 0) { ratio *= 10; x = tmp; } }

        
        return ratio;
    }
    
public:
    bool isPalindrome(int x) {
        if (x < 0)
            return false;
        
        auto first = 1;
        auto last = largest_ratio(x);
        while (first < last) {
            if ((x / first % 10) != (x / last % 10))
                return false;
            first *= 10, last /= 10;
        }
        
        return true;
    }
};
