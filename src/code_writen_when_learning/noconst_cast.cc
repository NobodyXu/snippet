struct A {
    operator int () { return 1; }
};
int main() {
    const A a;
    int i = a;
}
