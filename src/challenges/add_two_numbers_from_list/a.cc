#include <new>
#include <iterator>
#include <algorithm>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

class ListHead
{
    ListNode *begin_p;
    
    struct backInsertIt
    {
        ListNode *curr_p = nullptr;
        
        using difference_type = void;
        using value_type = int;
        using pointer = value_type*;
        using reference = value_type&;
        using iterator_category	= std::output_iterator_tag;
              
        // This should never be used
        bool operator != (const backInsertIt&) const noexcept
        {
            return true;
        }
        
        auto& operator * () const noexcept
        {
            return curr_p->val;
        }
    
        auto* operator -> () const noexcept
        {
            return &curr_p->val;
        }
              
        auto& operator ++ ()
        {
            auto next_p = new ListNode;
            
            curr_p->next = next_p;
            curr_p = next_p;
            
            return *this;
        }
        
        auto operator ++ (int)
        {
            auto ret = *this;
            ++(*this);
            return ret;
        }
    };
public:
    ListHead(): begin_p{new ListNode}
    {}
    
    auto backInsertbegin() noexcept
    {
        return backInsertIt{begin_p};
    }
    auto backInsertend() noexcept -> backInsertIt
    {
        return {};
    }
    
    auto release() noexcept
    {
        auto ret = begin_p;
        begin_p = nullptr;
        return ret;
    }
    
    ~ListHead()
    {
        auto curr_p = begin_p;
                
        while (curr_p != nullptr) {
            auto next_p = curr_p->next;
            
            delete curr_p;
            curr_p = next_p;
        }
    }
};

struct list_it 
{
    ListNode *curr_p = nullptr;
    
    using difference_type = void;
    using value_type = int;
    using pointer = value_type*;
    using reference = value_type&;
    using iterator_category	= std::input_iterator_tag;
          
    // This should never be used
    bool operator != (const list_it&) const noexcept
    {
        return curr_p != nullptr;
    }
    
    auto& operator * () const noexcept
    {
        return curr_p->val;
    }
    
    auto* operator -> () const noexcept
    {
        return &curr_p->val;
    }
    
    auto& operator ++ ()
    {
        curr_p = curr_p->next;
        
        return *this;
    }
    
    auto operator ++ (int)
    {
        auto ret = *this;
        ++(*this);
        return ret;
    }
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListHead lists{};
        
        std::transform(list_it{l1}, list_it{}, list_it{l2}, lists.backInsertbegin(),
                       [carry = 0](const int &x, const int &y) mutable noexcept {
                           auto addition_result = x + y + carry;
                           carry = addition_result >= 10 ? 1 : 0;
                           return addition_result >= 10 ? addition_result - 10 : addition_result;
                       });
        return lists.release();
    }
};
