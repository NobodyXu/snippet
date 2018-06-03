#ifndef __algorithm_range_range_HPP__
# define __algorithm_range_range_HPP__
namespace algorithm::range {
template <class _It1, class _It2>
struct range {
    _It1 _beg;
    _It2 _end;

    constexpr auto begin() const noexcept { return _beg; }
    constexpr auto end() const noexcept { return _end; }
};
template <class It1, class It2> range(const It1&, const It2&) -> range<const It1&, const It2 &>;
} /* algorithm::range */
#endif
