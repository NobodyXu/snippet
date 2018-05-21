#include <cstdio>
void F() { 1 + 2; }
int main() {
    F(); 
    printf("%d\n", noexcept(F()));
}
