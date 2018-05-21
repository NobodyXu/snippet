#include <iostream>
void A() { std::cout << "Hello, world!\n"; }
void B(void A()) { A(); }
int main() { B(A); }
