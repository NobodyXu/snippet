#ifndef __concept_check_disambiguation_types_HPP__
#define __concept_check_disambiguation_types_HPP__
namespace concept_check {
struct disambiguation_t2 {};
struct disambiguation_t1 {
    constexpr operator disambiguation_t2 () const noexcept { return {}; }
};
}
#endif
