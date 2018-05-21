#include <cstdio>
struct A {
    virtual void F() const noexcept {}
};
int main() {
    printf("sizeof(A) = %lu\n, sizeof(A[10]) = %lu.\n", 
	    sizeof(A), sizeof(A[10]));
}
