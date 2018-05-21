#include <iostream>
#include <type_traits>
template<class From, class To>
inline constexpr const bool is_convertible_v = std::is_convertible<From, To>::value;
template <class T>
inline constexpr const bool is_convertible_to_l_ref_v = is_convertible_v<T, T&>;
template <class T>
inline constexpr const bool is_convertible_to_r_ref_v = is_convertible_v<T, T&&>;

template <class T>
struct output {};
template <class T>
std::ostream& operator << (std::ostream &os, output<T>) {
    return os << "is_convertible_to_l_ref: " << is_convertible_to_l_ref_v<T> << std::endl
	      << "is_convertible_to_r_ref: " << is_convertible_to_r_ref_v<T> << std::endl;
}
template <class T>
std::ostream& operator << (std::ostream &os, output<T&>) {
    return os << "is_convertible_to_r_ref: " << is_convertible_to_l_ref_v<T> << std::endl;
}
template <class T>
std::ostream& operator << (std::ostream &os, output<T&&>) {
    return os << "is_convertible_to_l_ref: " << is_convertible_to_l_ref_v<T> << std::endl;
}
#define _OUTPUT_(type) "\n" #type ":\n\n" << output<type>{}
#define _OUTPUT(type) _OUTPUT_(type) << _OUTPUT_(type &) << _OUTPUT_(type &&)
#define OUTPUT(type) _OUTPUT(signed type) << _OUTPUT(unsigned type)

struct A {};
struct B {
    operator B& ();
};
struct C {
    operator C&& ();
};
struct D {
    operator D& ();
    operator D&& ();
};
int main() {
    std::cout << std::boolalpha

	      << OUTPUT(char)
	      << OUTPUT(short)
	      << OUTPUT(int)
	      << OUTPUT(long)
	      << OUTPUT(long long)
	      << _OUTPUT(float)
	      << _OUTPUT(double)
	      << _OUTPUT(A)
	      << _OUTPUT(B)
	      << _OUTPUT(C)
	      << _OUTPUT(D);
}
