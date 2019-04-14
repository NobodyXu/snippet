// This is a failed solution
// This only works for situations where either l1 or l2 is 0 or both of them have the same size.
#include <new>
#include <iterator>
#include <algorithm>

struct ListNode
{
    int val;
    ListNode *next = nullptr;

    constexpr ListNode(int x) noexcept: val(x)
    {}
};

class ListHead
{
    ListNode *begin_p = nullptr;
    
    struct InsertIt
    {
        ListNode **next_ptr_p = nullptr;
        mutable int tmp;
        
        using difference_type = void;
        using value_type = int;
        using pointer = value_type*;
        using reference = value_type&;
        using iterator_category	= std::output_iterator_tag;
              
        // This should never be used
        constexpr bool operator != (const InsertIt&) const noexcept
        {
            return true;
        }
        
        // The value returned is the value of dereferencing the previous iterator
        auto operator * () const -> reference
        {
            return tmp;
        }
    
        // The value returned is the value of dereferencing the previous iterator
        auto operator -> () const -> pointer
        {
            return &tmp;
        }
              
        auto& operator ++ ()
        {
            *next_ptr_p = new ListNode{tmp};
            next_ptr_p = &((*next_ptr_p)->next);
            
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
    ListHead() = default;
    
    auto Insertbegin() noexcept
    {
        return InsertIt{&begin_p};
    }
    auto Insertend() noexcept -> InsertIt
    {
        return {};
    }
    
    auto release() noexcept
    {
        auto ret = begin_p;
        begin_p = nullptr;
        return ret;
    }
    
    ~ListHead() noexcept
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
        
        if (l1->val == 0)
            return l2;
        if (l2->val == 0)
            return l1;

        std::transform(list_it{l1}, list_it{}, list_it{l2}, lists.Insertbegin(),
                       [carry = 0](const int &x, const int &y) mutable noexcept {
                           auto addition_result = x + y + carry;
                           carry = addition_result >= 10 ? 1 : 0;
                           return addition_result >= 10 ? addition_result - 10 : addition_result;
                       });
        return lists.release();
    }
};
