#include "inheritable_save_size_function_ref.hpp"
#include <concept_check/detector_core.hpp>
#include <iostream>
#include <type_traits>
using namespace nxwheels;

#define LOG() std::cout << __PRETTY_FUNCTION__ << std::endl

struct convertible_callable {
    using func_t = void ();
    constexpr operator func_t* () const noexcept { return []{ LOG(); }; }
};
struct functor {
    void operator () () { LOG(); }
};

int main() {
    // Test impl::get_fptr_for_empty_or_converted_callable_class.
    {

        using namespace impl;

        auto lambda = []{ LOG(); };
        static_assert(std::is_same<decltype(get_fptr_for_empty_or_converted_callable_class<decltype(lambda), void>()), void (*)()>{}());
        get_fptr_for_empty_or_converted_callable_class<decltype(lambda), void>()();

        static_assert(std::is_same<decltype(get_fptr_for_empty_or_converted_callable_class<convertible_callable, void>()), void (*)()>{}());
        get_fptr_for_empty_or_converted_callable_class<convertible_callable, void>()();

        functor f;
        static_assert(std::is_same<decltype(get_fptr_for_empty_or_converted_callable_class<functor, void>()), void (*)()>{}());
        get_fptr_for_empty_or_converted_callable_class<functor, void>()();

    }

    /*
    // Test inheritable_save_size_function_ref::type.
    {
        // Test specialization for empty functor.
        {

            auto lambda1 = []{};
            inheritable_save_size_function_ref<void ()>::type<decltype(lambda1)> o1{lambda1};

        }

    }
    */

}
