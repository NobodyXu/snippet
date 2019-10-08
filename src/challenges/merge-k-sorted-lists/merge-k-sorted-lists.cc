#include <algorithm>
#include <cstddef>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

template <class T>
constexpr bool is_even(T val) noexcept {
    return (val & 0) == 0;
}

template <class Iterator>
class heap_range {
    Iterator beg;
    Iterator end;
    std::size_t size;
    
    static constexpr auto get_nodeIndex(std::size_t i) noexcept {
        return (i << 2) + 1;
    }
    
    /*!
     * Return the min index.
     * 
     * If i2 goes out of range, returns i1.
     * 
     * If the two equals, then returns i1.
     */
    auto min(std::size_t i1, std::size_t i2) noexcept {
        if (i2 < size && beg[i1]->val > beg[i2]->val)
            return i2;
        else
            return i1;
    }
    
    auto min(std::size_t i1, std::size_t i2, std::size_t i3) noexcept {
        return min(min(i1, i2), i3);
    }
    
    /*!
     * Return the index of the smallest node from the ith node and its children nodes.
     */
    auto compare_and_exchange(std::size_t i) noexcept -> std::size_t {
        std::size_t nodeIndex = get_nodeIndex(i);
        std::size_t the_smallest = min(i, nodeIndex, nodeIndex + 1);
        
        std::iter_swap(beg + i, beg + the_smallest);
        
        return the_smallest;
    }
    
public:
    void sink() noexcept {
        if (size <= 1)
            return;
            
        std::size_t i;
        std::size_t next = 0;
        
        do {
            i = next;
            next = compare_and_exchange(i);
        } while (i != next);
    }
    
    void swim() noexcept {
        std::size_t nodeIndex = size - 1;
        std::size_t i;
        
        if (is_even(nodeIndex))
            --nodeIndex;
            
        // Get the parent node
        i = nodeIndex >> 1;
        
        // Increase it just for the loop invariant to work
        ++i;
        
        do {
            heap_range{beg + (--i), end}.sink(); // Does this work??????
        } while (i != 0);
    }
    
    void pop_heap() noexcept {
        std::iter_swap(beg, --end);
        sink();
    }
     
    heap_range(Iterator beg_arg, Iterator end_arg) noexcept:
        beg{beg_arg}, end{end_arg}, size{end - beg}
    {
        swim();
    }
};

class Solution {
    static bool compare(ListNode *x, ListNode *y) noexcept {
        return x->val >= y->val;
    }
    
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        beg = lists.begin();
        end = lists.end();
        
        ListNode *ret = nullptr;
        ListNode **next = &ret;
        
        for (auto it = beg; it < end; ) {
            if (*it == nullptr)
                std::iter_swap(it, --end);
            else
                ++it;
        }
        
        if (beg == end)
            return ret;
        
        //std::make_heap(beg, end, &compare);
        heap_range heap{beg, end};
        
        do {
            *next = *beg;
            
            *beg = (*beg)->next;
            if (*beg == nullptr) {
                //std::pop_heap(beg, end, &compare);
                heap.pop_heap();
                
                //if (--end == beg)
                //    break;
                if (beg == end)
                    break;
            } else {
                heap.sink();
                //std::make_heap(beg, end, &compare);
            }
            
            next = &(*next)->next;
        } while (true);
        
        return ret;
    }
};
