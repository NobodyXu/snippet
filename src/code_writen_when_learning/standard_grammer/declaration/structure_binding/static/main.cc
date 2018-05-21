auto F() noexcept {
    struct {
	int a;
	char b;
	void *p;
    } a{1111, 'L', nullptr};
    return a;
}

static auto [a, b, p] = F();
int main() {}
