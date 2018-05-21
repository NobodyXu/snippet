#include <iostream>
#include <iterator>
#include "range.hpp"
using namespace algorithm::range;
int main() {
    std::basic_istream<char>::sync_with_stdio(false);
    std::ostreambuf_iterator out(std::cout);
    for(char c: range{std::istreambuf_iterator(std::cin), std::istreambuf_iterator<char>()})
	*out = c;
}
