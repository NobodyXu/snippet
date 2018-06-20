int main() {
    auto f = [] {
        int i;
        ++i;
    };
    static_assert(noexcept(f()));
}
