#ifndef  __twoSum_testcases_HPP__
# define __twoSum_testcases_HPP__

# include <vector>
# include <array>
# include <initializer_list>
# include <utility>
# include <iostream>

struct Case
{
    std::vector<int> nums;
    int target;
    std::pair<int, int> answer;

    bool check_result(const std::vector<int> &result) const noexcept
    {
        return (result[0] == answer.first && result[1] == answer.second) ||
               (result[1] == answer.first && result[0] == answer.second);
    }
};

auto& operator << (std::ostream &os, const Case &a_case)
{
    os << "nums:\n";

    for (auto &each: a_case.nums)
        os << each << std::endl;

    os << "\ntarget: " << a_case.target << std::endl
       << "\nanswer: " << a_case.answer.first << " " << a_case.answer.second << std::endl;
    return os;
}

template <class D, class ...Args>
constexpr auto make_array(Args &&...args) -> std::array<D, sizeof...(Args)>
{
    return {std::forward<Args>(args)...};
}

static const auto cases = make_array<Case>(
    Case{{3, 2, 4}, 6, {1, 2}}
);

#endif
