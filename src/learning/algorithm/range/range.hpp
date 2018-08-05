#ifndef __algorithm_range_range_HPP__
# define __algorithm_range_range_HPP__

namespace nxwheels {
template <class _It1, class _It2>
struct range {
    _It1 _beg;
    _It2 _end;

    constexpr auto begin() const noexcept { return _beg; }
    constexpr auto end() const noexcept { return _end; }
};
template <class It1, class It2> range(const It1&, const It2&) -> range<It1, It2>;
} /* nxwheels */
#endif
