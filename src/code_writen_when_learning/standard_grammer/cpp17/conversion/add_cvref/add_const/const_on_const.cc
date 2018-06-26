template <class T> using add_const_t = const T;

int main() {
    add_const_t<int> ci0{0};
    add_const_t<const int> ci1{1};
}
