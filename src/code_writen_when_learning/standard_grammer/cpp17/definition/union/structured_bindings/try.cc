struct S {
    int i;
    char c;
};

union U {
    int i;
    char c;
};

template <class T> using as = T;

template <class T, auto [x] = *as<T*>{nullptr}>
auto  F(int) -> int {}
int main() {
    // auto [x] = U{1};
    F<S>();
}
