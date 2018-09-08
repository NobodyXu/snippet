#ifndef __algorithm_range_range_HPP__
# define __algorithm_range_range_HPP__

namespace nxwheels {
template <class _It1, class _It2>
struct range {
    _It1 _beg;
    _It2 _end;

    range() = default;

    range(const range&) = default;
    range(      range&&) = default;

    range& operator = (const range&) = default;
    range& operator = (      range&&) = default;

    constexpr range(const _It1 &it1, const _It2 &it2 = _It2{}) noexcept : _beg{it1}, _end{it2} {}
    template <class Range>
    constexpr range(Range &&rng) noexcept : _beg{rng.begin()}, _end{rng.end()} {}

    constexpr auto& begin() const noexcept { return _beg; }
    constexpr auto& end() const noexcept { return _end; }

    constexpr auto& begin() noexcept { return _beg; }
    constexpr auto& end() noexcept { return _end; }
};
template <class Range> range(Range &&rng) -> range<decltype(rng.begin()), decltype(rng.end())>;
} /* nxwheels */
#endif
