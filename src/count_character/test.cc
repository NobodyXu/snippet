#include "character_count.hpp"

#include <cstdlib>
#include <csignal>
#include <iostream>

void test_to_str_len(std::size_t in, std::size_t out) noexcept
{
    assert(to_str_len<std::size_t>(in) == out);
}

void test_reverse_str(const char *in, const char *out)
{
    std::string s(in);
    reverse_str(s.begin(), s.end());
    assert(s == out);
}

void test_uitos(std::size_t in, const char *out, std::size_t size)
{
    std::string s;
    s.resize(size);
    assert(s.end() == uitos(s.begin(), in));
    assert(s == out);
}

void test_r_uitos(std::size_t in, const char *out, std::size_t size)
{
    std::string s;
    s.resize(size);
    assert(s.begin() == r_uitos(s.end() - 1, in) + 1);
    assert(s == out);
}

void test_count_repeat(const char *in, std::size_t len, std::size_t out) noexcept
{
    assert(count_repeat<std::size_t>(in, in + len) == out);
}

void test_r_count_repeat(const char *last, std::size_t out) noexcept
{
    assert(r_count_repeat<std::size_t>(last) == out);
}

character_count<> obj("aaaaaabcc");

[[noreturn]] void assertion_failure_handler(int) noexcept
{
    std::cerr << obj.get_result() << std::endl;
    std::exit(EXIT_FAILURE);
}

int main()
{
    std::signal(SIGABRT, &assertion_failure_handler);

    test_to_str_len(0, 1);
    test_to_str_len(9, 1);
    test_to_str_len(10, 2);
    test_to_str_len(20000, 5);
		       
    test_reverse_str("12345", "54321");
    test_uitos(111, "111", 3);  
    test_r_uitos(211, "211", 3); 
    test_count_repeat("222", 3, 3);
    test_count_repeat("33332", 5, 4);
    test_r_count_repeat("33332" + 4, 1);
    test_r_count_repeat("3333222" + 6, 3);

    assert(obj.process().get_result() == "a6b1c2");
    assert(obj.set_string("abcdefg").process().get_result() == "a1b1c1d1e1f1g1"); 
    assert(obj.set_string("aaaabcdefgaaaaaaa").process().get_result() == "a4b1c1d1e1f1g1a7");
    assert(obj.set_string("abcdefgaaaaaaaaaaaaaaaaaaaa").process().get_result() == "a1b1c1d1e1f1g1a20");
    assert(obj.set_string("abcdefgaa").process().get_result() == "a1b1c1d1e1f1g1a2");
}
