#include <iostream>
#include <type_traits>
template <class T>
void F(T &) { std::cout << std::is_const<T>{}(); }
int main() {
    std::cout << std::boolalpha;
    const int &i0 = 1;
    int i = 0;
    int &i1 = i;
    F(i0);
    F(i1);
}
