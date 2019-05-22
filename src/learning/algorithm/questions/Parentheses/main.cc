#include <iostream>
#include <sstream>
#include <algorithm>
#include <cassert>
#include <cstddef>

auto readall(std::istream &in) {
    std::ostringstream ss;

    std::ios_base::sync_with_stdio(false);
    in.tie();
    in.exceptions(std::ios_base::badbit);
    ss.exceptions(std::ios_base::badbit);

    in >> ss.rdbuf();

    return ss.str();
}

[[gnu::noinline]] auto find_endof_left_parentheses(char *beg, char *end) noexcept {
    do {
        if (*beg != '[' && *beg != '(' && *beg != '{')
            break;
        ++beg;
    } while(beg != end);
    return beg;
}
[[gnu::noinline]] void convert_left_parentheses_into_right_ones(char *beg, char *end) noexcept {
    std::for_each(beg, end, [](char &c) {
        char add = 2;
        if (c == '(')
            add -= 1;
        c += add;
    });
}
[[gnu::noinline]] auto detect_and_convert_left_parentheses_into_right_ones(char *beg, char *end) noexcept {
    auto endof_left_parentheses = find_endof_left_parentheses(beg, end);
    convert_left_parentheses_into_right_ones(beg, endof_left_parentheses);
    return endof_left_parentheses;
}
[[gnu::noinline]] auto match_converted_left_parentheses_with_right_ones(char *begof_left, const std::size_t sizeof_left, char *begof_right, const std::size_t sizeof_right) noexcept {
    bool ret;
    if (!sizeof_left || sizeof_left > sizeof_right)
        ret = 0;
    else
        ret = std::equal(begof_left, begof_left + sizeof_left, begof_right);
    return ret;
}
bool detect_broken_parentheses(char *i, char *end) {
    assert(i < end);

    bool ret;
    do {
        auto endof_left_parentheses = detect_and_convert_left_parentheses_into_right_ones(i, end);

        auto sizeof_left = endof_left_parentheses - i;
        ret = match_converted_left_parentheses_with_right_ones(i, sizeof_left, endof_left_parentheses, end - endof_left_parentheses);
        i = endof_left_parentheses + sizeof_left;
    } while(i != end && ret);

    return ret;
}

int main() {
    auto string = readall(std::cin);
    std::cout << std::boolalpha
              << detect_broken_parentheses(&string[0], &string[string.size() - 1]) << std::endl;
}
