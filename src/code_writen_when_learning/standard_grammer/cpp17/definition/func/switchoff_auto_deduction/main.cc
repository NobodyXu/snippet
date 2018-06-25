template <class T> using as = T;

template <class T>
constexpr void f(T, as<T>) noexcept {}

int main() {
    f(4.3, 9);
}
