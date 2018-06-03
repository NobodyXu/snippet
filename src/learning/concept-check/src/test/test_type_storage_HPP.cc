#include <iostream>
#include "impl/type_storage.hpp"
using namespace concept_check;
int main() {
    std::cout << element_T<3, int, long, unsigned, char>{'c'} << std::endl
              << type_storage_element_T<3, type_storage<int, long, unsigned, char>>{'d'} << std::endl;
}
