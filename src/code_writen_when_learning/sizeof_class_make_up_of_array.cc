#include <cstdio>
struct empty {};
struct A {
    void (*fptr[0])(void);
    int a[0];
    char b[0];
};
union B {
    int a[0];
    char b[0];
};
int main() { 
    printf("sizeof(A) = %lu\nsizeof(empty) = %lu\nsizeof(B) = %lu",
	    sizeof(A), sizeof(empty), sizeof(B));
}
