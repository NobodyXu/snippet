#ifndef __nobodyxu_wheels_dynamic_connectivity_WeightedQuickUnionUF_v1_HPP__
# define __nobodyxu_wheels_dynamic_connectivity_WeightedQuickUnionUF_v1_HPP__

# include "UF_api.hpp"

namespace nxwheels::dyn_conn {
template <class Int>
struct ValueWithWeight {
    Int val, weight;

    using self = ValueWithWeight;
    ValueWithWeight() = default;

    ValueWithWeight(const self&) = default;
    ValueWithWeight(self&&) = default;

    self& operator = (const self&) = default;
    self& operator = (self&&) = default;

    constexpr ValueWithWeight(Int Val, Int Weight = 1) noexcept : val{Val}, weight{Weight} {}
};
template <class Int>
struct WQU_UF_v2: UF_impl1<Int, WQU_UF_v2<Int>, ValueWithWeight<Int>> {
    using base = UF_impl1<Int, WQU_UF_v2, ValueWithWeight<Int>>;
    using Id_t = ValueWithWeight<Int>;

    void Union(Int p, Int q) noexcept {
        auto &[pid, pWeight] = findRootPair(p);
        auto &[qid, qWeight] = findRootPair(q);

        if (pid == qid)
            return;

        if (pWeight < qWeight) {
            pid = qid;
        } else {
            qid = pid;
            pWeight = pWeight == qWeight ? qWeight + 1 : qWeight;
        }

        --base::count;
    }
    Int findRoot(Int p) const noexcept {
        while (base::_id[p].val != p)
            p = base::_id[p].val;
        return p;
    }
    auto& findRootPair(Int p) const noexcept {
        while (base::_id[p].val != p)
            p = base::_id[p].val;
        return base::_id[p];
    }
protected:
    auto& findRootPair(Int p) noexcept {
        while (base::_id[p].val != p)
            p = base::_id[p].val;
        return base::_id[p];
    }
};
} /* nxwheels::dyn_conn */
#endif
