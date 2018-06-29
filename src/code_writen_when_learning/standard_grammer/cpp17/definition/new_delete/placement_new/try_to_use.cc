using size_t = decltype(sizeof(int));
void* operator new(size_t sz, void *p) {
    return p;
}
void F() noexcept {
    new ((void*) 1) int();
}
int main() {
}
