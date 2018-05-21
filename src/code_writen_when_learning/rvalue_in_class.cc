#include <cstdio>
struct A {
    int &&u;
};
int main() {
    A{int{0}};
}
