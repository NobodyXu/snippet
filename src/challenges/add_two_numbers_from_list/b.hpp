#include <cstdint>
#include <new>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <array>

struct ListNode
{
    int val;
    ListNode *next = nullptr;

    constexpr ListNode(int x) noexcept: val(x)
    {}
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
    
    auto begin() const noexcept -> list_it
    {
        return {begin_p};
    }

    auto end() const noexcept -> list_it
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

/*
 * The first stores the result;
 * The second stores the ratio (10, 100, 1000) to convert the next digit to an integer it represents;
 * The third stores number of digits.
 */
using result_t = std::array<std::uint64_t, 3>;
auto converter(const result_t &prev_result, int val) noexcept
{
    result_t ret;

    ret[0] = static_cast<std::uint64_t>(prev_result[0] + val * prev_result[1]);
    ret[1] = prev_result[1] * 10;
    ret[2] = prev_result[2] + 1;

    return ret;
}

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListHead lists{};

        auto op1 = std::accumulate(list_it{l1}, list_it{}, result_t{0, 1, 0}, converter);
        auto op2 = std::accumulate(list_it{l2}, list_it{}, result_t{0, 1, 0}, converter);

        const auto result = op1[0] + op2[0];

        auto digits = std::max(op1[2], op2[2]);
        if (result >= std::max(op1[1], op2[1]))
            digits += 1;
        
        std::generate_n(lists.Insertbegin(), digits, [&result, mask = 10]() mutable noexcept {
            auto ret = result % mask;
            mask *= 10;
            return ret;
        });

        return lists.release();
    }
};
