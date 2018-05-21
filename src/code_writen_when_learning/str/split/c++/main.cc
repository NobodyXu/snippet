/*
 * C++17
 * The model of the input string:
 *
 * (optional) delimiter | content | delimiter | content | delimiter|
 * ... | delimiter | content
 *
 * Using std::string::find_first_not_of or
 * std::string_view::find_first_not_of is a bad idea, because it
 * actually does the following thing:
 *
 *     Finds the first character not equal to any of the characters
 *     in the given character sequence.
 *
 * Which means it does not treeat your delimiters as a whole, but as
 * a group of characters.
 *
 * This has 2 effects:
 *
 *  1. When your delimiters is not a single character, this function
 *  won't behave as you predicted.
 *
 *  2. When your delimiters is just a single character, the function
 *  may have an additional overhead due to the fact that it has to
 *  check every character with a range of characters, although
 * there's only one, but in order to assure the correctness, it still
 * has an inner loop, which adds to the overhead.
 *
 * So, as a solution, I wrote the following code.
 *
 * The code below will skip the first delimiter prefix.
 * However, if there's nothing between 2 delimiter, this code'll
 * still treat as if there's sth. there and push it into the container.
 *
 */
#include <cstdio>
#include <string_view> // new feature in C++17, sizeof(std::string_view) == 16 in libc++ on my x86-64 debian 9.4 computer.

namespace linux {
#include <sys/mman.h>
} /* linux */

// The loop invariant:
//  1. At pos, it is the content that should be saved.
//  2. The next pos of delimiter is stored in next, which could be 0 or max_size()
//  or std::string_view::npos.
struct brute_force_search {
    std::pair<const char*, const char * const> str;
    std::pair<const char * const, const char * const> delimiter;

    brute_force_search(std::string_view _str, std::string_view _delimiter) noexcept:
        str{_str.data(), _str.data() + _str.size()}, delimiter{_delimiter.data(), _delimiter.data() + _delimiter.size()} {}

    struct iterator {
        brute_force_search *data;
        const char *next;

        typename std::string_view::size_type delimiter_size = data->delimiter.second - data->delimiter.first;

        iterator() = default;
        iterator(brute_force_search *obj) noexcept: data{obj} {
            find_next();

            if (next == pos()) {
                // Establish the loop invariant 1.
                pos() = next + delimiter_size;
                // Establish the loop invariant 2.
                find_next();
            }
        }

        constexpr bool operator != (const iterator &it) const noexcept {
            return next != nullptr;
        }
        constexpr auto& operator ++ () noexcept {
            // Establishment of loop invariant 1.
            pos() = next + delimiter_size;
            // Establishment of loop invariant 2.
            find_next();

            return *this;
        }
        constexpr auto operator * () noexcept {
            return std::string_view{pos(), next - pos()};
        }
      protected:
        auto& pos() noexcept {
            return data->str.first;
        }
        void find_next() noexcept {
            if (pos() >= data->str.second)
                next = nullptr;
        }
    };

    constexpr iterator begin() noexcept { return {this}; }
    constexpr iterator end() const noexcept { return {}; }
};

template <class Search, template <class...> class Container, class Allocator>
void split_forrange(Container<std::string_view, Allocator> &tokens,
            const std::string_view str,
            const std::string_view delimiter = " ")
{
    for(auto token: Search{str, delimiter})
        tokens.push_back(token);
}

int main() {
    // Get data
    std::fprintf(stderr, "C++   : Saw %lu lines (%lu words/%lu chars) in %lu seconds.  Crunch speed: %.1f \n", (double) count / sec);
}
