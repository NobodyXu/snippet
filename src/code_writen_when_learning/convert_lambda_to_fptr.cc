#include <cstdio>
auto F() noexcept { 
    return static_cast<const char* (*)(void)>([](){ 
	    return "Hello, World!\n";
    }); 
}
int main() noexcept { printf("%s\n", F()()); }
