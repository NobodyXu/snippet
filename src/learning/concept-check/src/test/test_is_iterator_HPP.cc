#include <iostream>
#include "is_iterator.hpp"
using namespace concept_check;

template <class T>
struct def_pre_inc_op {
    auto& operator ++ () noexcept { ++(get_T_ref().ptr); return get_T_ref(); }
private:
    T& get_T_ref() noexcept { return *((T*)this); }
};
template <class T>
struct def_post_inc_op {
    auto operator ++ (int) noexcept { auto ret{*this}; ++(get_T_ref().ptr); return ret; }
private:
    T& get_T_ref() noexcept { return *((T*)this); }
};
template <class T>
struct def_incr_op:def_pre_inc_op<T>, def_post_inc_op<T> {};

struct A {
    using difference_type   = long long;
    using value_type        = int;
    using pointer           = int*;
    using reference         = int&;
    using iterator_category = std::random_access_iterator_tag;
    int *ptr;
};
struct B: A {
  reference operator * () const noexcept { return *ptr; }
};
struct C:B, def_pre_inc_op<C> {};

#define OUTPUT_is_it(type) "\nis_it_v<" #type ">: " << is_it_v< type > << std::endl
int main() {
    std::cout << std::boolalpha

              << OUTPUT_is_it(A)
              << OUTPUT_is_it(B)
              << OUTPUT_is_it(C);
}
