#include <iostream>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/include/vector.hpp>

int main() {
    boost::fusion::vector<int, int, int> vec;

    for(auto &x: vec)
	std::cout << x << std::endl;
}
