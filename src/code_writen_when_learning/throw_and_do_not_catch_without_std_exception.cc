#include <exception>
struct A {
    virtual const char* what() const noexcept { return "Hello, World!\n"; }
};
int main() { throw A{}; }
