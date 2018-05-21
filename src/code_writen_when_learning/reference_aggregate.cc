template <class A, class B>
struct Foo {
    A &a;
    A &b;
    A &c;
    B &d;
};
//both works
//template <class A, class B> Foo(A, A, A, B) -> Foo<A, B>;
template <class A, class B> Foo(A&, A&, A&, B&) -> Foo<A, B>;
int main() {
    int a{1}, b{2}, c{3};
    char d{'2'};
    Foo f{a, b, c, d};
}
