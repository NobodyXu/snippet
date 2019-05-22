#ifndef __container_list_H__
#define __container_list_H__
# include <cstddef>
namespace container {
template <class List>
struct ListEntry {
    List *entry;
};
namespace listNode {
namespace listNodeIterators {
# define DECL_ET_F(CLASS_NAME, T, TAG, FUNC_NAME) extern template decltype(auto) CLASS_NAME < T, TAG > :: FUNC_NAME ()
template <class T, class tag>//T should be a kind of listNode
struct iterator_base {//iterator base is a kind of forwrd iterator
	using difference_type = std::size_t;
	using value_type = T;
	using pointer = value_type*;
	using referemce = value_type&;
	using iterator_category = tag;
	T *curr;
	decltype(auto) operator *() const noexcept { return (*curr); }
	decltype(auto) operator ->() const noexcept { return (*curr;) }
	decltype(auto) operator ++() noexcept { curr = curr->next; return (*this); }
	[[deprecated]]decltype(auto) operator ++(int) noexcept { auto ret = *this; ++(*this); return ret; }
	//should I add bit operation overload functions here?
	decltype(auto) operator ==(const iterator &oth) const noexcept { return curr == oth.curr; }
	decltype(auto) operator !=(const iterator &oth) const noexcept { return curr != oth.curr; }
	decltype(auto) operator!() const noexcept { return !curr; }
	operator decltype(auto)() const noexcept { return static_cast<bool>(curr); }
};
//The extern template declaration of member functions of iterator_base
extern template decltype(auto) iterator_base<unaryListNode, std::forward_iterator_tag>::operator *() const noexcept;
extern template decltype(auto) iterator_base<binaryListNode, std::bidrection_iterator_tag>::operator *() const noexcept;
extern template decltype(auto) iterator_base<binary_stored_in_one_ListNode, std::random_access_iterator_tag>::operator *() const noexcept;

extern template decltype(auto) iterator_base<unaryListNode, std::forward_iterator_tag>::operator ->() const noexcept;
extern template decltype(auto) iterator_base<binaryListNode, std::bidrection_iterator_tag>::operator ->() const noexcept;
extern template decltype(auto) iterator_base<binary_stored_in_one_ListNode, std::random_access_iterator_tag>::operator ->() const noexcept;

extern template decltype(auto) iterator_base<unaryListNode, std::forward_iterator_tag>::operator ++() noexcept;
extern template decltype(auto) iterator_base<binaryListNode, std::bidrection_iterator_tag>::operator ++() noexcept;
extern template decltype(auto) iterator_base<binary_stored_in_one_ListNode, std::random_access_iterator_tag>::operator ++() noexcept;

extern template [[deprecated]] decltype(auto) iterator_base<unaryListNode, std::forward_iterator_tag>::operator ++(int) noexcept;
extern template [[deprecated]] decltype(auto) iterator_base<binaryListNode, std::bidrection_iterator_tag>::operator ++(int) noexcept;
extern template [[deprecated]] decltype(auto) iterator_base<binary_stored_in_one_ListNode, std::random_access_iterator_tag>::operator ++(int) noexcept;

extern template decltype(auto) iterator_base<unaryListNode, std::forward_iterator_tag>::operator ==() const noexcept;
extern template decltype(auto) iterator_base<binaryListNode, std::bidrection_iterator_tag>::operator ==() const noexcept;
extern template decltype(auto) iterator_base<binary_stored_in_one_ListNode, std::random_access_iterator_tag>::operator ==() const noexcept;

extern template decltype(auto) iterator_base<unaryListNode, std::forward_iterator_tag>::operator !=() const noexcept;
extern template decltype(auto) iterator_base<binaryListNode, std::bidrection_iterator_tag>::operator !=() const noexcept;
extern template decltype(auto) iterator_base<binary_stored_in_one_ListNode, std::random_access_iterator_tag>::operator !=() const noexcept;

extern template decltype(auto) iterator_base<unaryListNode, std::forward_iterator_tag>::operator !() const noexcept;
extern template decltype(auto) iterator_base<binaryListNode, std::bidrection_iterator_tag>::operator !() const noexcept;
extern template decltype(auto) iterator_base<binary_stored_in_one_ListNode, std::random_access_iterator_tag>::operator !() const noexcept;

extern template iterator_base<unaryListNode, std::forward_iterator_tag>::operator decltype(auto)() const noexcept;
extern template iterator_base<binaryListNode, std::bidrection_iterator_tag>::operator decltype(auto)() const noexcept;
extern template iterator_base<binary_stored_in_one_ListNode, std::random_access_iterator_tag>::operator decltype(auto)() const noexcept;

template <class T>//T should be iterator_base
struct bidirection_iterator_adapter {
    auto& operator --() noexcept { auto &curr = get_curr(); curr = curr->prev; return *this; }
    [[deprecated]]auto operator --(int) noexcept { auto ret = *this; ++(*this); return ret; }
private:
    T& getT() noexcept { return *static_cast<T*>(this); }
    auto& get_curr() noexcept { return getT().curr; }
};
template <class T, class tag>//type T should be a kind o listNode
struct bidirection_iterator: bidirection_iterator_adapter<iterator_base<T, tag>>, iterator_base<T, tag> {};

template <class T >
struct random_access_iterator {
    bidirection_iterator<T, std::random_access_iterator_tag>
    //+, -, +=, -=, []
};
}//namespace listNodeIterators
struct unaryListNode {
    unaryListNode *next;
    void append(unaryListNode*) noexcept;
    void removeNext() noexcept;
    using iterator = listNodeIterators::iterator_base<unaryListNode, std::foward_iterator_tag>;
};
struct binaryListNode {
    binaryListNode *prev, *next;
};
struct binary_stored_in_one_ListNode {
    binary_stored_in_one_ListNode *bi_ptr;
};
template <class
struct skiplist {};
}//namespace ListNode
}//namespace NB
#endif
