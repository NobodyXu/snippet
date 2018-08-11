#ifndef __nobodyxu_wheels_inheritable_save_size_function_ref_HPP__
# define __nobodyxu_wheels_inheritable_save_size_function_ref_HPP__

# include <type_traits>
# include <utility>
# include <concept_check/utility.hpp>
# include <concept_check/concepts/operations/is_convertible_v.hpp>
# include <concept_check/concepts/operations/is_callable_v.hpp>

namespace nxwheels::impl {
template <class T, class Ret, class ...Args>
auto get_fptr_for_empty_or_converted_callable_class() noexcept -> Ret (*)(Args...) noexcept(is_nothrow_callable_impl_v<T, Args...>) {
    if constexpr(is_implicitly_convertible_v<T, Ret (*)(Args...)>)
        return *static_cast<T*>(nullptr);
    else
        return [](Args &&...args) noexcept(is_nothrow_callable_impl_v<T, Args...>) -> decltype(auto) {
            return (*static_cast<T*>(nullptr))(args...);
        };
}
} /* nxwheels::impl */

namespace nxwheels {
template <class Expected_F>
struct inheritable_save_size_function_ref;
template <class Ret, class ...Args>
struct inheritable_save_size_function_ref<Ret (Args...)> {
    template <class T, bool = std::is_empty<T>{}()>
    class type;

    template <class T>
    class type<callable_t<T, Args...>, true> {
    public:
        template <class U>
        constexpr type(U&&) noexcept {}

        inline static auto fptr = impl::get_fptr_for_empty_or_converted_callable_class<T, Ret, Args...>();
        constexpr decltype(auto) operator () (Args &&...args) const noexcept( noexcept(fptr(std::forward<Args>(args)...)) ) {
            return fptr(std::forward<Args>(args)...);
        }

        static auto& get_value() noexcept { return fptr; }
    };
    template <class T>
    class type<callable_t<T, Args...>, false> {
    public:
        T obj;

        constexpr decltype(auto) operator () (Args &&...args)       noexcept( noexcept(obj(std::forward<Args>(args)...)) ) {
            return obj(std::forward<Args>(args)...);
        }
        constexpr decltype(auto) operator () (Args &&...args) const noexcept( noexcept(obj(std::forward<Args>(args)...)) ) {
            return obj(std::forward<Args>(args)...);
        }

        auto& get_value()       noexcept { return obj; }
        auto& get_value() const noexcept { return obj; }
    };

    template <class T> type(T) -> type<T>;
};
} /* nxwheels */
#endif
