#include <iostream>
int main() {
    int integer;
    std::cin >> integer;
    signed char ch = static_cast<signed char>(integer);
    if(ch < 0) std::cout << "<0";
    else if(ch == 0) std::cout << "=0";
    else std::cout << ">0";
}
