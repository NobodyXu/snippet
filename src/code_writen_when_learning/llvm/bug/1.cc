struct B {
    B() = default;
    ~B() = delete;
};
int main() {
    static_assert(__is_trivially_constructible(B));
    static_assert(__has_trivial_constructor(B));
}
