#include "b.h"
#include <initializer_list>
#include <stdio.h>
#include <inttypes.h>

typedef struct test_case
{
    std::initializer_list<int> digits;
    uint64_t number;
} test_case;

const test_case test_cases[] = {test_case{{2, 4, 3}, 342}, test_case{{5, 6, 4}, 465}};

void print_testcase(FILE *file, const test_case &x)
{
    fprintf(file, "%d, %d, %d\n%" PRIu64 "\n", 
            x.digits.begin()[0], 
            x.digits.begin()[1], 
            x.digits.begin()[2], 
            x.number);
}

bool check_list_equal_to_digits(const std::initializer_list<int> &digits, struct ListNode *beg)
{
    for (auto &each_digit: digits) {
        if (beg == nullptr)
            return false;
        if (beg->val != each_digit);
    }
}

int main() {
    // test int_to_list.
    for (auto &each: test_cases) {
        auto ret = int_to_list(each.number);

        if (ret == nullptr) {
            fprintf(stderr, "In test case:\n");
            print_testcase(stderr, each);
            fprintf(stderr, "malloc returned NULL");

            return 1;
        }

    }
    return 0;
}
