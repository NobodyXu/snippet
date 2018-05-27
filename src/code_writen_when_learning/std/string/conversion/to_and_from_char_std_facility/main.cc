 // See en.cppreference.com for more information, including format control.
#include <cstdio>
#include <cstddef>
#include <cstdlib>
#include <cassert>
#include <charconv>

using Type =  /* Any fundamental type */ ;
std::size_t buffer_size = /* ... */ ;

[[noreturn]] void report_and_exit(int ret, const char *output) noexcept
{
    std::printf("%s\n", output);
    std::exit(ret);
}
void check(const std::errc &ec) noexcept
{
    if (ec ==  std::errc::value_too_large)
        report_and_exit(1, "Failed");
}
int main() {
    char buffer[buffer_size];
    Type val_to_be_converted, result_of_converted_back;

    auto result1 = std::to_chars(buffer, buffer + buffer_size,  val_to_be_converted);
    check(result1.ec);
    *result1.ptr = '\0';

    auto result2 = std::from_chars(buffer, result1.ptr, result_of_converted_back);
    check(result2.ec);

    assert(val_to_be_converted == result_of_converted_back);
    report_and_exit(0, buffer);
}
