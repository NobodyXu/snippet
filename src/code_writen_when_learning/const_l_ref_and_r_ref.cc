#include <iostream>
#define OUTPUT() std::cout << __PRETTY_FUNCTION__ << std::endl
template <class T>
void F(const T &t) { OUTPUT() << t << std::endl; }
template <class T>
void F(T &&t) { OUTPUT() << t << std::endl; }
int main() {
    const int &i1{0};
    int &&i2{1};
    F(i1);
    F(i2);
    F(1);
    typedef const int cint;
    F(cint{10});
    cint i3{12};
    F(i3);
}
