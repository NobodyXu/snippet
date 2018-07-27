#ifndef __nobodyxu_wheels_dynamic_connectivity_WeightedQuickUnionUF_v2_with_PathCompresson_HPP__
# define __nobodyxu_wheels_dynamic_connectivity_WeightedQuickUnionUF_v2_with_PathCompresson_HPP__

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
struct WQU_UF_v2_with_PC: UF_impl1<Int, WQU_UF_v2_with_PC<Int>, ValueWithWeight<Int>> {
    using base = UF_impl1<Int, WQU_UF_v2_with_PC, ValueWithWeight<Int>>;
    using Id_t = ValueWithWeight<Int>;

    void Union(Int p, Int q) noexcept {
        auto &[pid, pWeight] = findRootPair(p);
        auto &[qid, qWeight] = findRootPair(q);

        if (pid == qid)
            return;

        if (pWeight < qWeight)
            pid = qid;
        else if (pWeight > qWeight)
            qid = pid;
        else {
            qid = pid;
            ++pWeight;
        }

        --base::count;
    }
    Int findRoot(Int p) const noexcept {
        return findRootPair(p).val;
    }
    auto& findRootPair(Int p) const noexcept {
        while (base::_id[p].val != p)
            p = base::_id[p].val;
        return base::_id[p];
    }
protected:
    auto& findRootPair(Int p) noexcept {
        if (base::_id[p].val != p) {
            auto i = p;
            do {
                i = base::_id[i].val;
            } while(base::_id[i].val != i);

            auto ret = i;
            do {
                i = base::_id[p].val;
                base::_id[p].val = ret;
                p = i;
            } while(base::_id[i].val != i);

            return base::_id[ret];
        } else
            return base::_id[p];
    }
};
} /* nxwheels::dyn_conn */
#endif
