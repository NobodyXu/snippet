#include <iostream>
#include <algorithm>
#include <experimental/filesystem>
#include "configure_io.hpp"
namespace filesystem = std::experimental::filesystem;

template <class T> using unmodifiable_ptr = const T * const;
int main(const int argc, const unmodifiable_ptr<char> argv[]) try {
    configure::configure_io(std::cout, std::cin, std::cerr);
    std::for_each(argv, argv + argc, [](unmodifiable_ptr<char> str) {
	if (filesystem::path path{str}; filesystem::exists(path))
	    std::cout << file_size(path);
	else 
	    std::cerr << "path " << str << " does not exist." << std::endl;
    });
} catch(const std::system_error &err) {
    if (std::cerr) std::cerr << err.what();
    return 1;
}
