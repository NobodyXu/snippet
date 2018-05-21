#include <iostream>
#include <iterator>
using std::iterator_traits;
template <class T>
using It_val = typename iterator_traits<T>::value_type;

# include "impl/macro/define_has_member_type.hpp"
using namespace concept_check;
create_fn_has_member_type_alias(iter, It_val<T>)
# include "impl/macro/undef_has_member_type.hpp"

struct A {
    typedef int difference_type;
};
struct B {
    using difference_type   = long long;
    using value_type	    = int;
    using pointer	    = int*;
    using reference	    =  int&;
    using iterator_category = std::random_access_iterator_tag;
};

int main() {
    std::cout << std::boolalpha
	      << has_type_alias_iter_v<A> << std::endl
	      << has_type_alias_iter_v<B> << std::endl;
}
