#ifndef __nobodyxu_wheels_dynamic_connectivity_QuickFind_UF_HPP__
# define __nobodyxu_wheels_dynamic_connectivity_QuickFind_UF_HPP__

# include "UF_api.hpp"

namespace nxwheels::dyn_conn {
template <class Int>
struct QF_UF: UF_impl1<Int, QF_UF<Int>> {
    using base = UF_impl1<Int, QF_UF<Int>>;
    void Union(Int p, Int q) noexcept {
        auto pid = base::_id[p];
        auto qid = base::_id[q];

        if (pid == qid)
            return;

        for (auto &id: base::_id)
            id = id == pid ? qid : id;
        --base::count;
    }
    void findRoot(Int p) const noexcept { return base::_id[p]; }
};
} /* nxwheels::dyn_conn */
#endif
