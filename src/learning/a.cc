#include <iostream>

auto out_ = [](const auto &val)
{
    std::cout << val;
};

auto print_ = [](auto &&first_param, auto &&...params)
{
    out_(first_param);
    int a[] = {(out_(params), 1)...};
};

template <class F>
struct wrapper 
{
    F f;

    template <class ...Args>
    auto& operator () (Args &&...args)
    {
	f(args...);
	return *this;
    }
};
template <class F> wrapper(F) -> wrapper<F>;

auto print = wrapper{print_};

int main()
{
    print("Hello, ", "you there, ")("this is from ")("clang ", __VERSION__, "!"); 
}
