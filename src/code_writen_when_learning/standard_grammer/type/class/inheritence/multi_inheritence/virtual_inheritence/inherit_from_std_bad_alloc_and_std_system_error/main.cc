//#include <cstdio>
#include <new>
#include <system_error>

struct A: public std::system_error, public std::bad_alloc {};

int main() {
    A a;

    //std::printf("sizeof(A) = %lu, \nsizeof(std::system_error) = %lu, \nsizeof(std::bad_alloc) = %lu\n",
                 //sizeof(A),         sizeof(std::system_error),         sizeof(std::bad_alloc));
}
