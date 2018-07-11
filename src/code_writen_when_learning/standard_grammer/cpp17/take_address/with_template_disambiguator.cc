struct A {
    void F() {}
    template <class = void>
    void F() {}
};

int main() {
    auto pf1 = &A::template F<>;
}
