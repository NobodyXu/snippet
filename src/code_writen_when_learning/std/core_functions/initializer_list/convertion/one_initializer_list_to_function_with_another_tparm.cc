#include <initializer_list>
#include <utility>
void func(std::initializer_list<int>) {}
struct A {
    A(std::initializer_list<int> il) {}
};
int main() {
    func({'c', 'd'});
    func({'c', 'd', short{33}});

    A{1, 1, 'c'};
    A{{1, 1, 'c'}};
    using type = decltype( new A({std::declval<int>(), std::declval<int>(), std::declval<char>()}) );
}
