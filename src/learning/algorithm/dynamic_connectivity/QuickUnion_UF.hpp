#ifndef __nobodyxu_wheels_dynamic_connectivity_QuickUnionUF_HPP__
# define __nobodyxu_wheels_dynamic_connectivity_QuickUnionUF_HPP__

# include "UF_api.hpp"

namespace nxwheels::dyn_conn {
template <class Int>
struct QU_UF: UF_impl1<Int, QU_UF<Int>> {
    using base = UF_impl1<Int, QU_UF>;
    void Union(Int p, Int q) noexcept {
        auto pid = findRoot(p);
        auto qid = findRoot(q);

        if (pid == qid)
            return;

        base::_id[qid] = pid;
        --base::count;
    }
    Int findRoot(Int p) const noexcept {
        while (base::_id[p] != p)
            p = base::_id[p];
        return p;
    }
};
} /* nxwheels::dyn_conn */
#endif
