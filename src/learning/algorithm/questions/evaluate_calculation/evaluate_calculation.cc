#include "evaluate_calculation.hpp"

#include "../../range/range.hpp"
#include <string_view>
#include <charconv>
#include <cmath>
namespace evaluate_calculation {
auto evaluate_calculation::operator () () noexcept(false) {
    process();
    return get_result();
}
void evaluate_calculation::process() noexcept(false) {
    for(std::string_view str: range::range{beg, istream_it{}})
        switch (str[0]) {
            default:
                operand_stack.emplace(read_operand(str));
                break;
            case ')':
                operands.push(evaluate_top_element());
                break;

            case 's':
                if (str != "sqrt")
                    throw exception{exception::error_code::unrecognized_op};
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
                ops.emplace(str[0]);
            case '(':
        }
}
auto evaluate_calculation::read_operand(std::string_view str) noexcept(false) {
    Operand_t operand;

    const char *str_beg = str.data(), *str_end = str_beg + str.size();
    exception e{exception::error_code::invalid_operand};

    switch(std::from_chars(str_beg, str_end, operand).ec) {
        case std::errc::invalid_argument:
        case std::errc::result_out_of_range:
            e.e_code = exception::error_code::operand_out_of_range;
            throw e;
        default:
            return operand;
    }
}
auto evaluate_calculation::evaluate_top_element() noexcept {
    Operand_t ret;
    auto v2 = operands.pop();

    switch (ops.pop()) {
        case 's': ret = static_cast<Operand_t>(std::sqrt(v2));
        case '+': ret = ops.pop() + v2;
        case '-': ret = ops.pop() - v2;
        case '*': ret = ops.pop() * v2;
        case '/': ret = ops.pop() / v2;
        case '%': ret = ops.pop() % v2;
    }
    return ret;
}
auto evaluate_calculation::get_result() noexcept {
    return operands.pop();
}
} /* evaluate_calculation */
