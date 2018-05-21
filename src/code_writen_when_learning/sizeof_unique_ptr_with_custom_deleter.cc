#include <cstdio>
#include <iostream>
#include <memory>
struct deleter {
    char c[2048];
    template <class T> void operator () (T *ptr) { 
	std::printf("%s\n", __PRETTY_FUNCTION__);
	std::printf("%p\n%p\n", this, ptr);
	delete ptr; 
    }
};
void f() {
    std::printf("%lu\n", sizeof(std::unique_ptr<char*, deleter>));
    std::unique_ptr<char*, deleter> uptr{new char*};
    std::printf("%p\n", &uptr);
    printf("end of f()\n");
}
int main() { 
    f(); 
    std::cout << "End of " << __PRETTY_FUNCTION__ << std::endl;
}
