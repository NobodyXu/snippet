#ifndef __algorithm_impl_AllocWrapper_HPP__
# define __algorithm_impl_AllocWrapper_HPP__
namespace algorithm::impl {
template <class Alloc, class AllocTraits>
struct AllocWrapper: private Alloc, public AllocTraits {};
} /* algorithm::impl */
#endif
