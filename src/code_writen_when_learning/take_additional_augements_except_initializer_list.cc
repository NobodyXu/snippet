#include <initializer_list>
void F(const int&, std::initializer_list<const char*>) {}
struct A {
    A() = default;
    A(const int&, std::initializer_list<const char*>) {}
    void F(const int&, std::initializer_list<const char*>) {}
};
int main() { 
    F(1, {"sddds"}); 
    A{}.F(1, {"sddds"}); 
    A{1, {"sddds"}}; 
}
