#include <algorithm>
#include <cstddef>
T
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

template <class T>
constexpr auto get_nodeIndex(T i) noexcept {
    return (i << 2) + 1;
}    

template <class Iterator>
class heap_range {
    Iterator beg;
    Iterator end;
    std::size_t size;

    /*!
     * Return the min index.
     * 
     *  - If i2 goes out of range, returns i1;
     *  - If the two equals, then returns i1.
     * 
     * This is an important quality as this feature enables `void sink(std::size_t)`
     * to return early if no exchange between parent and children nodes happen at all.
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
     * 
     * Only exchanges when the parent node is bigger than any child node.
     * If any child node equals each other, consider the one with smaller index first.
     */
    auto compare_and_exchange(std::size_t i) noexcept -> std::size_t {
        std::size_t nodeIndex = get_nodeIndex(i);
        std::size_t the_smallest = min(i, nodeIndex, nodeIndex + 1);
        
        std::iter_swap(beg + i, beg + the_smallest);
        
        return the_smallest;
    }
    
public:
    void sink(std::size_t start) noexcept {
        if (size - start <= 1)
            return;
            
        std::size_t i;
        std::size_t next = start;
        
        do {
            i = next;
            next = compare_and_exchange(i);
        } while (i != next);
    }
    
    void swim() noexcept {
        if (size <= 1)
            return;
            
        std::size_t nodeIndex = size - 1;
        std::size_t i;
        
        if (is_even(nodeIndex))
            --nodeIndex;
            
        // Get the parent node
        i = nodeIndex >> 1;
        
        // Increase it just for the loop invariant to work
        ++i;
        
        do {
            sink(--i);
        } while (i != 0);
    }
    
    void pop_heap() noexcept {
        std::iter_swap(beg, --end);
        --size;
        sink(0);
    }
    
    bool is_empty() const noexcept {
        return beg == end;
    }
    
    auto& top() noexcept {
        return *beg;
    }
     
    heap_range(Iterator beg_arg, Iterator end_arg) noexcept:
        beg{beg_arg}, end{end_arg}, size{end - beg}
    {
        swim();
    }
};

template <class It>
auto remove_null(It beg, It end) noexcept {
    for (auto it = beg; it < end; )
        if (*it == nullptr)
            std::iter_swap(it, --end);
        else
            ++it;
    
    return end;
}

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode *ret = nullptr;
        ListNode **next = &ret;
        
        heap_range heap{lists.begin(), remove_null(lists.begin(), lists.end())};
        
        if (heap.is_empty())
            return ret;
        
        do {
            *next = heap.top();
            
            heap.top() = heap.top()->next;
            if (heap.top() == nullptr) {
                heap.pop_heap();

                if (heap.is_empty())
                    break;
            } else
                heap.sink(0);
            
            next = &(*next)->next;
        } while (true);
        
        return ret;
    }
};
