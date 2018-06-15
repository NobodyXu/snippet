template <class T>
struct wrapper {
    using self = wrapper;

    T obj;

    auto operator + () const noexcept { return *this; }
    auto operator - () const noexcept { return self{0} - *this; }

    auto operator + (const self &other) const noexcept { return self{*this} += other; }
    auto operator - (const self &other) const noexcept { return self{*this} -= other; }

# define DEF_ASSIGN(OP)\
    auto& operator OP ## = (const self &other) noexcept {\
        obj OP ## = other.obj;\
        return *this;\
    }
    
    DEF_ASSIGN(+)
};
int main() {
    auto result = wrapper<int>{3} + wrapper<int>{4};
}
