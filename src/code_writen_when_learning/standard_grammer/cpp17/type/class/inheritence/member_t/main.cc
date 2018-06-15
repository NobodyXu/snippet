struct Base {
    typedef int type;
};
struct Derived: Base {
    typedef type type2;
    type A() { return {1}; }
};
int main() {
    typename Base::type t1{222};
    typename Derived::type t2{2333};
    typename Derived::type2 t3{2333};
    auto ret = Derived{}.A();
}
