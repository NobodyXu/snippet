#ifndef __type_erasure_basic_storage_any_wrapper_class_HPP__
# define __type_erasure_basic_storage_any_wrapper_class_HPP__
# include <cstfddef>
# include <utility>
namespace type_erasure {
struct any_wrapper_base1 {
    using self = any_wrapper_base1;
    static inline constexpr const bool has_vtable{0};

    std::size_t _size_of_the_derived_class;
    void (*clone)(void*, const void*);
    void (*move)(void*, void*);
    void (*dtor)(void*);

    template <class T>
    constexpr any_wrapper_base1(T*) noexcept : _size_of_the_derived_class{sizeof(T)},
                                               clone{[](void *p1, const void *p2){ new (p1) T(*static_cast<const T*>(p2)); }},
                                               move {[](void *p1, void *p2)      { new (p1) T(std::move(*static_cast<T*>(p2))); }},
                                               dtor {[](void *p)                 { static_cast<T*>(p)->~T(); }}
    {}
};
template <class T, class _Base>
struct any_wrapper_for_inheritence: _Base {
    using Base = _Base;

    T obj;
    constexpr any_wrapper_for_inheritence(const T &_obj): obj(_obj), Base(T*{}) {}
};
} /* type_erasure */
#endif
