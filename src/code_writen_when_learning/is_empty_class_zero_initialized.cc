#include <cstdio>
struct empty {};
int main() {
    empty e;
    printf("%d\n", *static_cast<char*>(static_cast<void*>(&e)));
}
