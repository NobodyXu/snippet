#include <iostream>
#include <string>
int main() { 
    std::string s;
    short integer{1};
    std::cout << sizeof(short) << "integer = " << integer << std::endl;
    std::cin >> integer >> s;
    std::cout << "integer = " << integer << std::endl;
    std::cout << s << std::endl;
    return 0;
}
