int main() {
    void (*fp)(void) = [](){};
    typedef void (*fpt)(void);
    fpt fp1{[](){}};
}
