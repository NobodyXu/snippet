#include <cstdio>
#include <cstring>
int main() {
    for(int i{0}; i != 134; ++i) printf("%s\n", std::strerror(i)); 
}
