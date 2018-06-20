struct A {};
struct B {
    B() = default;
    explicit B(const A&) {}
};
int main() {
    auto result = static_cast<B>(A{});
}
