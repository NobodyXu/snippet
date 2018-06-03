#include "list.h"
namespace container {
namespace listNode {
namespace listNodeIterator {
//The extern template declaration of member functions of iterator_base
template decltype(auto) iterator_base<unaryListNode, std::forward_iterator_tag>::operator *() const noexcept;
template decltype(auto) iterator_base<binaryListNode, std::bidrection_iterator_tag>::operator *() const noexcept;
template decltype(auto) iterator_base<binary_stored_in_one_ListNode, std::random_access_iterator_tag>::operator *() const noexcept;

template decltype(auto) iterator_base<unaryListNode, std::forward_iterator_tag>::operator ->() const noexcept;
template decltype(auto) iterator_base<binaryListNode, std::bidrection_iterator_tag>::operator ->() const noexcept;
template decltype(auto) iterator_base<binary_stored_in_one_ListNode, std::random_access_iterator_tag>::operator ->() const noexcept;

template decltype(auto) iterator_base<unaryListNode, std::forward_iterator_tag>::operator ++() noexcept;
template decltype(auto) iterator_base<binaryListNode, std::bidrection_iterator_tag>::operator ++() noexcept;
template decltype(auto) iterator_base<binary_stored_in_one_ListNode, std::random_access_iterator_tag>::operator ++() noexcept;

template [[deprecated]] decltype(auto) iterator_base<unaryListNode, std::forward_iterator_tag>::operator ++(int) noexcept;
template [[deprecated]] decltype(auto) iterator_base<binaryListNode, std::bidrection_iterator_tag>::operator ++(int) noexcept;
template [[deprecated]] decltype(auto) iterator_base<binary_stored_in_one_ListNode, std::random_access_iterator_tag>::operator ++(int) noexcept;

template decltype(auto) iterator_base<unaryListNode, std::forward_iterator_tag>::operator ==() const noexcept;
template decltype(auto) iterator_base<binaryListNode, std::bidrection_iterator_tag>::operator ==() const noexcept;
template decltype(auto) iterator_base<binary_stored_in_one_ListNode, std::random_access_iterator_tag>::operator ==() const noexcept;

template decltype(auto) iterator_base<unaryListNode, std::forward_iterator_tag>::operator !=() const noexcept;
template decltype(auto) iterator_base<binaryListNode, std::bidrection_iterator_tag>::operator !=() const noexcept;
template decltype(auto) iterator_base<binary_stored_in_one_ListNode, std::random_access_iterator_tag>::operator !=() const noexcept;

template decltype(auto) iterator_base<unaryListNode, std::forward_iterator_tag>::operator !() const noexcept;
template decltype(auto) iterator_base<binaryListNode, std::bidrection_iterator_tag>::operator !() const noexcept;
template decltype(auto) iterator_base<binary_stored_in_one_ListNode, std::random_access_iterator_tag>::operator !() const noexcept;

template iterator_base<unaryListNode, std::forward_iterator_tag>::operator decltype(auto)() const noexcept;
template iterator_base<binaryListNode, std::bidrection_iterator_tag>::operator decltype(auto)() const noexcept;
template iterator_base<binary_stored_in_one_ListNode, std::random_access_iterator_tag>::operator decltype(auto)() const noexcept;

}//namespace listNodeIterator
void unaryListNode::append(unaryListNode *l2) noexcept {
    l2->next = next;
    next = l2;
}
auto unaryListNode::removeNext() noexcept {
    auto temp = next;
    next = temp->next;
    return temp;
}
}//namespace listNode
}//namespace NB
