#include <iostream>
#include <fstream>
#include <boost/cstdint.hpp>
#include "QuickFind_UF.hpp"

template <class T>
using UF = nxwheels::dyn_conn::QF_UF<T>;

int main(int argc, char *argv[]) {
    if (argc != 2)
        return -1;

    std::ifstream in{argv[1]};
    UF<boost::uint64_t> uf{};

    uf.fromStream(in);
    std::cout << uf.Count() << std::endl;
}
