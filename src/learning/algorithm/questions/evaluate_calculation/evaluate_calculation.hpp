#ifndef __algorithm_questions_evaluate_calculation_evaluate_calculation_HPP__
# define __algorithm_questions_evaluate_calculation_evaluate_calculation_HPP__

# include <iostream>
# include <iterator>
# include <string>

# include <cstdint>
# include <vector>
# include <stack>

namespace evaluate_calculation {
struct evaluate_calculation {
    using Operand_t = std::int64_t;
    using operator_t = char;
    using istream_it = std::istream_iterator<std::string>;
    using operand_stack = std::stack<Operand_t, std::vector<Operand_t>>;
    using operator_stack = std::stack<operator_t, std::vector<operator_t>>;

    struct exception {
        enum class error_code{
            unrecognized_op,
            operand_out_of_range,
            invalid_operand
        } e_code;
    };

    istream_it beg;

    operand_stack operands;
    operator_stack ops;

    auto operator () () noexcept(false);
  protected:
    void process() noexcept(false) ;

    auto read_operand() noexcept(false) ;
    auto evaluate_top_element() noexcept ;

    auto get_result() noexcept;
};
} /* evaluate_calculation */

#endif
