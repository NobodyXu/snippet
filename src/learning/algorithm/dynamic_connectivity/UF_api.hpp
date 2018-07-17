#ifndef __nobodyxu_wheels_dynamic_connectivity_UF_api_HPP__
# define __nobodyxu_wheels_dynamic_connectivity_UF_api_HPP__

# include <vector>

namespace nxwheels::dyn_union {
template <class Int, class Derived, class Content = Int>
struct UF_api {
    UF_api() = default;

    UF_api(const UF_api&) = default;
    UF_api(UF_api&&) = default;

    UF_api& operator = (const UF_api&) = default;
    UF_api& operator = (UF_api&&) = default;

    auto size() const noexcept { return get_Derived()->size(); }
    void addId(Int n) { get_Derived()->addId(n); }
    void clear() noexcept { get_Derived()->clear(); }

    void Union(Int p, Int q) noexcept { get_Derived()->Union(p, q); }
    Int findRoot(Int p) const noexcept { return get_Derived()->findRoot(p); }
    bool connected(Int p, Int q) const noexcept { return findRoot(p) == findRoot(q); }

    template <class Stream>
    void fromStream(Stream &&in) {
        clear();

        Int N, p, q;
        in >> N;
        addId(N);

        while(N--) {
            in >> p >> q;
            Union(p, q);
        }
    }

private:
    auto* get_Derived() noexcept { return static_cast<Derived*>(this); }
    auto* get_Derived() const noexcept { return static_cast<const Derived*>(this); }
};
template <class Int, class Derived, class Content = Int>
struct UF_impl1: UF_api<Int, Derived, Content> {
    auto size() const noexcept { return _id.size(); }
    void addId(Int n) {
        auto oldsize = size();
        _id.reserve(oldsize + n);

        Int i = oldsize;
        while (i != oldsize + n)
            _id.push_back(i++);

        count += n;
    }
    void clear() noexcept { _id.clear(); }
    Int Count() const noexcept { return count; }

protected:
    Int count{0};
    std::vector<Content> _id;
};
} /* nxwheels::dyn_union */
#endif
