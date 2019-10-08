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
class Solution {
    using iterator = typename vector<ListNode*>::iterator;
    
    iterator beg, end;
    
    static bool compare(ListNode *x, ListNode *y) noexcept {
        return x->val >= y->val;
    }
    
    static constexpr auto firstChildIndex(std::size_t i) noexcept {
        return (i << 2) + 1;
    }
       
    void sink() noexcept {
        for (std::size_t i = 0, size = end - beg, fChild = firstChildIndex(0); fChild < size; ) {
            if (fChild + 1 != size) {
                switch ((unsigned{beg[i]->val > beg[fChild]->val} << 1) | unsigned{beg[i]->val > beg[fChild + 1]->val}) {
                    case 3:
                        if (beg[fChild]->val > beg[fChild + 1]->val)
                            goto SWAP_WITH_sCHILD;
                            
                    case 2:
                        goto SWAP_WITH_fCHILD;
                        
                    case 1:
                        SWAP_WITH_sCHILD:
                        std::iter_swap(beg + i, beg + fChild + 1);
                        
                    case 0:
                        goto INCREMENT;
                        
                }
            } else if (beg[i]->val <= beg[fChild]->val)
                goto INCREMENT;
            
                
            SWAP_WITH_fCHILD:    
            std::iter_swap(beg + i, beg + fChild);
            
            INCREMENT:
            ++i;
            fChild = firstChildIndex(i);
        }
    }
    
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        beg = lists.begin();
        end = lists.end();
        
        ListNode *ret = nullptr;
        ListNode **next = &ret;
        
        for (auto it = beg; it < end; ) {
            if (*it == nullptr) {
                std::iter_swap(it, --end);
            } else
                ++it;
        }
        
        if (beg == end) {
            return ret;
        }
        
        std::make_heap(beg, end, &compare);
        
        do {
            *next = *beg;
            
            *beg = (*beg)->next;
            if (*beg == nullptr) {
                std::pop_heap(beg, end, &compare);
                
                if (--end == beg)
                    break;
            } else {
                sink();
                //std::make_heap(beg, end, &compare);
            }
            
            next = &(*next)->next;
        } while (true);
        
        return ret;
    }
};
