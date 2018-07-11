template <class T>
struct S {
    T *p;
    constexpr operator auto () const noexcept { return p; }
    constexpr auto operator -> () const noexcept { return p; }
};
template <class T> S(T*) -> S<T>;

int main() noexcept {
    int i;
    S s0{&i};
    S s1{&s0};
    s1->p;
}
