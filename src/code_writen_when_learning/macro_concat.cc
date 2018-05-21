#include <iostream>
#define cat(a, b) a##b
int main() {
    int ab{12232333};
    std::cout << cat(a, b) << std::endl;
}
