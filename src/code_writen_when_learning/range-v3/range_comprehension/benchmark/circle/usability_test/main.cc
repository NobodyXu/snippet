#include <iostream>
#include <range/v3/all.hpp>

using namespace ranges;

auto& operator << (std::ostream &os, const std::tuple<int, int, int> &triple) {
    return os << std::get<0>(triple) << ", " << std::get<1>(triple) << ", " << std::get<2>(triple);
}
int main() {
    auto triples = view::for_each(view::ints(1), [](int z)
    {
        return view::for_each(view::ints(1, z + 1), [=](int x)
        {
            return view::for_each(view::ints(x, z + 1), [=](int y)
            {
                return yield_if(x * x + y * y == z * z, std::make_tuple(x, y, z));
            });
        });
    });
    auto limited_triples = triples | view::take(10);

    for(auto triple: limited_triples)
        std::cout << triple << std::endl;

    for(auto triple: limited_triples)
        std::cout << triple << std::endl;
}
