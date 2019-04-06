#include "findtwoSum.hpp"
#include "testcases.hpp"

int main()
{
    Solution s;

    for (auto &a_case: cases) {
        auto result = s.twoSum(a_case.nums, a_case.target);

        if (!a_case.check_result(result)) {
            std::cerr << "Failure!\n" << a_case
                      << "\nResult: " << result[0] << " " << result[1] << std::endl;

            return 1;
        }
    }

    return 0;
}
