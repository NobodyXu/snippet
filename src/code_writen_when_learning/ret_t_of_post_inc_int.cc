#include <iostream>
#include <boost/cstdint.hpp>
#include <typeinfo>
template <class T>
T create_T();

template <class T>
void ret_t_of_pre_inc() {
    T i;
    std::cout << typeid(decltype(++i)).name() << std::endl
	      << typeid(T).name() << std::endl
	      << typeid(T&).name() << std::endl;
}
template <class T>
void ret_t_of_post_inc() {
    T i;
    std::cout << typeid(decltype(i++)).name() << std::endl
	      << typeid(T).name() << std::endl
	      << typeid(T&).name() << std::endl;
}
#define test(pos)		    \
ret_t_of_ ## pos ## _inc<int8_t>();  \
ret_t_of_ ## pos ## _inc<uint8_t>(); \
				    \
ret_t_of_ ## pos ##_inc<int16_t>();  \
ret_t_of_ ## pos ## _inc<uint16_t>();\
				    \
ret_t_of_ ## pos ## _inc<int32_t>(); \
ret_t_of_ ## pos ## _inc<uint32_t>();\
				    \
ret_t_of_ ## pos ## _inc<int64_t>(); \
ret_t_of_ ## pos ## _inc<uint64_t>();\
				    \
ret_t_of_ ## pos ## _inc<float>();  \
ret_t_of_ ## pos ## _inc<double>()

int main() {
    test(pre);
    test(post);
}
