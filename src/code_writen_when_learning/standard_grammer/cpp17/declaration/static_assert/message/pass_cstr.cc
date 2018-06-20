template <bool b, const char *msg>
struct assert {
    static_assert(b, msg);
};
int main() {
    assert<0, "2333"> a{};
}
