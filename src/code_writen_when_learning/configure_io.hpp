#ifndef __configure_configure_io__
#define __configure_configure_io__

#include <iostream>
#include <initializer_list>
#include <functional>

namespace configure {
namespace impl {
template <class Stream>
void configure_io(Stream &s) noexcept {
    s.exceptions(std::ios_base::badbit);
    s.sync_with_stdio(false);
    s.tie(nullptr);
}
}//namespace impl
template <class ...Stream>
void configure_io(Stream& ...s) noexcept {
    int a[] = {(impl::configure_io(s), 1)...};
}
}//namespace confiugre

#endif
