#include <iostream>
namespace impl{
namespace impl{
void F() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
}
void F() { impl::F(); }
}
int main() {
    impl::F();
}
