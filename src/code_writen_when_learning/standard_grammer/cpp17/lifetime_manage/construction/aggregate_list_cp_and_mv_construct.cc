#include <utility>
struct A {
    int i;
    char c;
};
int main() {
    A a = {A{2, '3'}};
    A a2 = {std::move(A{2, '3'})};
}
