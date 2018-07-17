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

    void size() const noexcept { return Nodes.size(); }
    void addNodes(Int n) {
        auto oldsize = size();
        Nodes.reserve(oldsize + n);

        Int i = oldsize;
        for(auto beg = Nodes.begin() + oldsize, end = Nodes.end(); beg != end; ++beg, ++i)
            Nodes.push_back(i);

        count += n;
    }
    void clear() noexcept { Nodes.clear(); }

    void Union(Int p, Int q) noexcept { get_Derived()->Union(p, q); }
    Int findRoot(Int p) noexcept { return get_Derived()->findRoot(p); }
    bool connected(Int p, Int q) noexcept { return findRoot(p) == findRoot(q); }
    Int Count() const noexcept { return count; }

    template <class Stream>
    void fromStream(Stream &&in) {
        clear();

        Int N, p, q;
        in >> N;
        addNodes(N);

        while(N--) {
            in >> p >> q;
            Union(p, q);
        }
    }

protected:
    Int count{0};
    std::vector<Content> Nodes;
private:
    auto* get_Derived() noexcept { return static_cast<Derived*>(this); }
    auto* get_Derived() const noexcept { return static_cast<const Derived*>(this); }
};
} /* nxwheels::dyn_union */
#endif
