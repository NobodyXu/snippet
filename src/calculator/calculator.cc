#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cassert>

template <int exp>
struct power_with_known_exp
{
    constexpr float operator () (float base) noexcept
    {
	if constexpr(exp > 0)
	    return base * power_with_known_exp<exp - 1>{}(base);
	else if constexpr(exp < 0)
	    return static_cast<float>(1) / (base * power_with_known_exp<-(exp) - 1>{}(base));
	else
	    return 1.0f;
    }
};

constexpr float power(float base, float exp)
{
# define CASE_IMPL(EXP)  \
    case EXP:	    \
	return power_with_known_exp<EXP>{}(base);
# define CASE(EXP) \
    CASE_IMPL(EXP);\
    CASE_IMPL(-EXP)

    if (auto nearexp = static_cast<int>(exp); static_cast<float>(nearexp) == exp)
	switch (nearexp) {
	    CASE_IMPL(0);
	    CASE(1);
	    CASE(2);
	    CASE(3);
	    CASE(4);
	    CASE(5);
	    CASE(6);
	    CASE(7);
	    CASE(8);
	    default:
		;
	}

    return std::pow(base, exp); // Fallback to slow std::pow

# undef  CASE
# undef  CASE_IMPL
}

void calculate(float a, char op, float b)
{
# define CASE(OP, OPNAME)						       \
    case #OP [0]:							       \
	std::cout << OPNAME " of two number is " << (a OP b) << "\n" << std::endl;\
	break

    switch(op) {
	CASE(+, "Addition");
	CASE(-, "Subtraction");
	CASE(*, "Multiplication");
	CASE(/, "Division");
	case 's':
	    std::cout << "Spuare root of the number is " << std::sqrt(b) << "\n" << std::endl;
	    break;
	case 'c':
	    std::cout << "Cubic root of the number is " << std::cbrt(b) << "\n" << std::endl;
	    break;
	case '^':
	    std::cout << "The power is " << power(a, b) << "\n" << std::endl;
	    break;
        default:
            std::cerr << "Unkown operator!" << "\n" << std::endl;
    }
    
# undef  CASE
}

/*!
 * Returns 0 when line is empty, 
 *         1 when too many chs,
 *         2 when nothing goes wrongs.
 */
int Getline(std::istream &in, std::string &line)
{
    std::getline(std::cin, line);

    // Check
    if (line.empty())
	return 0;
    else if (std::cin.fail()) {
	assert(line.size() == line.max_size());
	std::cerr << "\nToo many characters!" << std::endl;

	return 1;
    }

    return 2;
}

float Strtof(const char *beg, const char **end, const char *descrption)
{
    float ret = std::strtof(beg, const_cast<char**>(end));

    if (ret == HUGE_VALF) {
	std::cerr << descrption << "Value too large!" << std::endl;
	ret = NAN;
    }

    return ret;
}

const char* discard_space(const char *beg, const char *end)
{
    while (beg != end && *beg == ' ')
	++beg;
    return beg;
}

int main(int argc, char* argv[])
{
    int ret = 0;

    float a, b;
    char op;

    std::string line;
    const char *beg, *end;

    std::cout.exceptions(std::cout.failbit);
    std::cin.exceptions(std::cin.badbit);
    std::cerr.exceptions(std::cerr.failbit);

    std::cout << "This is a calculator program capable of +, -, *, /, s for square root, c for cubic root and ^ for power.\n"
		 "If you want to stop this program, simply enter nothing.\n"
	      << std::endl;

    while (true) {
	std::cout << "Enter any two operands:";

	switch(Getline(std::cin, line)) {
	    default:
		std::cerr << "\nGetline returns unknow value" << std::endl;
	    case 1:
		ret = 1;
	    case 0:
		goto out;
	    case 2:
		;
	}

	beg = line.data();

	a = Strtof(beg, &end, "The first operand: ");
	if (a == NAN)
	    continue;

	beg = end;
	end = line.data() + line.length();
	beg = discard_space(beg, end);
	if (beg == end) {
	    std::cerr << "Neither the operator nor the right operand is provided" << std::endl;
	    continue;
	}

	op = *beg++;

	b = Strtof(beg, &end, "The second operand: ");
	if (b == NAN)
	    continue;

	calculate(a, op, b);
    }

out:
    return ret;
}
