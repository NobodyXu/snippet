#include <iostream>
template <class T = int>
using _T = T;
int main() {
    std::cout << _T<char>{'c'} << std::endl
	      << _T<>{32332} << std::endl;
}
