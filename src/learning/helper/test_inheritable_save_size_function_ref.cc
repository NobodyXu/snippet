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

    // Test inheritable_save_size_function_ref::type.
    {
        std::cout << std::endl << "Test inheritable_save_size_function_ref::type." << std::endl;

        // Test specialization for empty functor.
        {

            auto lambda1 = []{ LOG(); };
            inheritable_save_size_function_ref<void ()>::type<decltype(lambda1)> o1{lambda1};
            o1();

            functor f;
            inheritable_save_size_function_ref<void ()>::type<functor> o2{f};
            o2();

        }

        // Test specialization for other callable objects.
        {

            int i;
            auto lambda = [&]{ LOG(); };
            inheritable_save_size_function_ref<void ()>::type<decltype(lambda)> o1{lambda};
            o1();

        }

    }

}
