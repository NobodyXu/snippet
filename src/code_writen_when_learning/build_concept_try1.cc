#include <iostream>
#include <iterator>
struct unambigious_t2 {};
struct unambigious_t1 {
    operator unambigious_t2 () { return {}; }
};
template <class T>
bool Foo(unambigious_t2) { return 0; }
template <class T, class = typename T::pointer>
bool Foo(unambigious_t1) { return 1; }
template <class It>
using It_traits = std::iterator_traits<It>;
int main() { 
    std::cout << std::boolalpha 
	      << Foo<It_traits<int*>>(unambigious_t1{}) << std::endl
	      << Foo<It_traits<int>>(unambigious_t1{})  << std::endl; 
}
