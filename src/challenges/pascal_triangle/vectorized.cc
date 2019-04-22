// C++14
#include <iostream>
#include <forward_list>
#include <array>
#include <iterator>
#include <cstdint>

template <class It1, class It2 = It1>
struct Range
{
    It1 beg_it;
    It2 end_it;

    auto begin() const noexcept { return beg_it; }
    auto end() const noexcept { return end_it; }
};

template <template <class...> class Container>
class pascal_triangle
{
    using value_t = std::uint64_t;
    using cIt = typename Container<value_t>::const_iterator;

    Container<value_t> data;

public:
    pascal_triangle(): data{0, 1}
    {}

    auto operator * () const noexcept -> Range<cIt>
    {
        return {std::next(data.begin()), data.end()};
    }

    auto& operator ++ ()
    {
        auto curr = data.begin();
        auto next = std::next(curr);
        auto end = data.end();

        do {
            *curr += *next;
            ++curr, ++next;
        } while(next != end);

        data.push_front(0);

        return *this;
    }
};

int main()
{
    std::uint64_t lines;

    std::cout << "Please enter lines: " << std::flush;
    std::cin >> lines;

    pascal_triangle<std::forward_list> pascal{};

    for (std::uint64_t line = 0; line != lines; ++line) {
        for (auto &each: *pascal)
            std::cout << each << " ";
        std::cout << std::endl << std::flush;

        ++pascal;
    }
}
