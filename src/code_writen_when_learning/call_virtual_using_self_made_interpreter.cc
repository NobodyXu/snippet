#include <iostream>
typedef const char* cstr;
template <class T, class Ret, class ...Args>
union member_fptr_t {
    Ret (T::*member_fptr)(Args...) const noexcept;
    struct {
        std::ptrdiff_t ptr;
        std::ptrdiff_t adj;
	void* get_ptr_of_virtual_function(void *_this) const noexcept { 
	    return 
		static_cast<void*>(
		    *static_cast<char**>(static_cast<void*>(static_cast<char*>(_this) + adj)) + (ptr - 1)
		);
	}
    } member_fptr_interpreter;
};
template <class Ret, class ...Args>
struct cast_to_mfptr {
    void *org_ptr;
    Ret (*mfptr)(void*, Args...);
};
template <class Ret, class ...Args>
constexpr auto static_cast_fptr(void *ptr) noexcept { return cast_to_mfptr<Ret, Args...>{ptr}.mfptr; }
struct A {
    virtual cstr F() const noexcept { return __PRETTY_FUNCTION__; }
    int i;
};
int main() {
    A a;
    auto inter = member_fptr_t<A, cstr>{&A::F}.member_fptr_interpreter;
    auto ptr_to_mf = inter.get_ptr_of_virtual_function(&a);
    std::cout << "The result of F is " << a.F() << std::endl
	      << "ptr = " << inter.ptr << ", adj = " << inter.adj << ";\n"
	      << "Pointer to virtual member function is: "  << ptr_to_mf 
	      << ", invoke result is " << static_cast_fptr<cstr>(ptr_to_mf)(&a) << std::endl;
}
