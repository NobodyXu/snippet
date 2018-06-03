//This file only support compilers using Itanium cxx abi.
#ifndef __type_erasure_view_view_any_callable_HPP__
# define __type_erasure_view_view_any_callable_HPP__
# include <cstddef>
# include <memory>
# include <utility>
# include <type_traits>
namespace type_erasure {
/*
 * Storage_impl_t is the class responsible for storing the type-erased object.
 * It is required to be able 1. to accept a pointer(probably nullptr) as the argument for nonexplicit ctor.
 *                           2. to be converted into a void* pointer pointed to the object managed by it.
 */
template <class Storage_impl_t>
struct any_callable_base {
    Storage_impl_t data;
    void (*fptr)();

    constexpr operator bool() const noexcept { return fptr; }
    constexpr bool operator!() const noexcept { return fptr != nullptr; }
  protected:
    template <class T, class Ret, class ...Args>
    static inline constexpr const bool is_convertible_to_plain_fptr_v{std::is_convertible<T, Ret (*)(Args...)>{}()};
    template <class T, bool is_noexcept, class Ret, class ...Args>
    static inline constexpr const auto _wrapper_f = [](void *_this, Args &&...args) noexcept(is_noexcept) {
        return (*static_cast<T*>(_this))(args...);
    };
  protected:
    template <bool _is_c_v, class T>
    static constexpr void* get_this(T &obj) noexcept {
        if constexpr(_is_c_v) return nullptr;
        else                  return std::addressof(obj);
    }
    template <class T>
    constexpr auto cast_to_generic_form(T &&obj) noexcept {
        return static_cast<void (*)()>(static_cast<Ret (*)(Args...) noexcept(is_noexcept)>(obj));
    }
    template <bool _is_c_v, class T, bool is_noexcept, class Ret, class ...Args>
    constexpr auto _get_fptr(T &obj) noexcept {
        if constexpr(_is_c_v) return cast_to_generic_form(obj);
        else                  return cast_to_generic_form(_wrapper_f<T, is_noexcept, Ret, Args...>);
    }
};
template <class F, class Storage_impl_t, class = void>
struct any_callable;
template <class Ret, class ...Args, class Storage_impl_t, class _Base = any_callable_base>
struct any_callable<Ret (*)(Args...), Storage_impl_t, void>: _Base {
  public:
    using F = Ret (*)(Args...);
    using self = any_callable;
    using Base = _Base;

    template <class T, bool _is_c_v = is_convertible_to_plain_fptr_v<T, F>>
    constexpr view_any_callable(T &&obj) noexcept: Base{get_this<_is_c_v>(obj), get_fptr<_is_c_v>(obj)} {}

    template <class T, bool _is_c_v = is_convertible_to_plain_fptr_v<T, F>>
    constexpr self& operator=(T &&obj) noexcept {
        data = get_this<_is_c_v>(obj);
        fptr = get_fptr<_is_c_v>(obj);
        return *this;
    }

    constexpr Ret operator () (Args ...args) {
        if (data) return static_cast<Ret (*)(void*, Args...)>(fptr)(data, args...);
        else      return static_cast<Ret (*)(Args...)>       (fptr)(      args...);
    }
  protected:
    template <bool _is_c_v, class T>
    constexpr auto get_fptr(T &obj) noexcept { return _get_fptr<_is_c_v, T, is_noexcept, Ret, Args...>(obj); }
};
/*
 * The following alias only provides a window to invoke a callable object, and it is not responsible for the store of the callable object
 * unless the callable object is
 *                               1. a pointer to non-member function;
 *                               2. a class which has overloaded function call operator, and the class is an empty class.
 */
template <class F> using view_any_callable = any_callable<F, void*>;
} /* type_erasure */
#endif
