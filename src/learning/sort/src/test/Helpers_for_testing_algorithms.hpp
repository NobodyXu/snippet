#ifndef __sort_Helpers_for_testing_algorithms_HPP__
#define __sort_Helpers_for_testing_algorithms_HPP__

# include <exception>
# include <cstddef>
# include <cstdio>
# include <cassert>
# include <string>
# include <initializer_list>

namespace c::posix {
# include <sys/syscall.h>
# define c_posix_get_syscall_num(SYSCALL_NAME) __NR_ ## SYSCALL_NAME

//These macros are defined to use xsi-compliant strerror_r version:
//   int strerror_r(int errnum, char *buf, size_t buflen);
//This file only support glibc version >= 2.13, as it use the return value of strerror_r to check whether it succeeds.
# undef  _GNU_SOURCE
# include <string.h>

//define _GNU_SOURCE so that program_invocation_name is accessiable.
# define _GNU_SOURCE     1
# include <errno.h>
inline error_t &get_errno() noexcept { return errno; }

# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>

void build_msg_on(char *buf, const std::size_t &buf_size,
                  const int &syscall_num, const char *const syscall_name, int _errno = errno) noexcept {
    auto ptr = buf +
    std::snprintf(buf, buf_size - 50 - 1, "syscall %d %s, errno = %d, meaning: ", syscall_num, syscall_name, _errno);
    assert(!strerror_r(_errno, ptr, 50));
}
//The buf will need 50 bytes for strerror_r in English context, 3 bhytes for displaying syscall_number,
//3 for displaying _errno, 22 for displaying syscall_name, 30 for format, and 1 for the trailing '0'.
inline constexpr const std::size_t recommanded_buf_size_for_exception_msg{50 + 3 + 6 + 22 + 30 + 1};
}//namespace c::posix


namespace sort::test {
struct exception: std::exception {
    static inline constexpr const std::size_t buf_size{1024};
    char msg[buf_size];
    //@ parameter descriptor
    //descriptor[0] __PRETTY_FUNCTION__, descriptor[1] __FILE__, descriptor[2] __VERSION__, descriptor[3] syscall_name
    exception(const int &syscall_num, const std::size_t &line, std::initializer_list<const char *> list_of_strs) noexcept {
        auto strs = list_of_strs.begin();
        auto cnt = std::snprintf(msg, buf_size - c::posix::recommanded_buf_size_for_exception_msg,
                                  "In %lu, %s, %s, compiled by %s, ", line, strs[0], strs[1], strs[2]);
        if(syscall_num) c::posix::build_msg_on(msg + cnt, buf_size - cnt, syscall_num, strs[3]);
    }
    const char* what() const noexcept { return msg; }
};
//usage example: exception NAME = sort_test_MK_exception(read);
# define sort_test_MK_exception(SYSCALL_NAME)                                                                          \
exception{c_posix_get_syscall_num(SYSCALL_NAME), __LINE__, {__PRETTY_FUNCTION__, __FILE__, __VERSION__, #SYSCALL_NAME }}

auto open(const char * const name, const int &flags) {
    int fd;
    do {
        fd = c::posix::open(name, flags);
    } while(c::posix::get_errno() == EINTR);
    if (fd != -1) return fd;
    else          throw sort_test_MK_exception(open);
}
auto get_file_size(const int &fd) {
    if (struct c::posix::stat buf; c::posix::fstat(fd, &buf) != -1) return buf.st_size;
    else                                                            throw sort_test_MK_exception(fstat);
}
auto read_until_success(const int &fd, void *ptr, const std::size_t &count) {
    int ret;
    int &_errno = c::posix::get_errno();
    do {
        ret = c::posix::read(fd, ptr, count);
    } while(_errno == EINTR || _errno == EAGAIN);
    if (ret >= 0) return ret;
    else          throw sort_test_MK_exception(read);
}
struct LoadFileIntoMem {
    void *ptr;
    LoadFileIntoMem() = default;
    LoadFileIntoMem(int fd): ptr{Do_load(fd)} {}

    LoadFileIntoMem(LoadFileIntoMem &&oth) noexcept: ptr{oth.ptr} { oth.ptr = nullptr; }
    LoadFileIntoMem(const LoadFileIntoMem&) = delete;

    LoadFileIntoMem& operator = (LoadFileIntoMem &&oth) noexcept {
        Do_unload();
        ptr = oth.ptr;
        oth.ptr = nullptr;
        return *this;
    }
    LoadFileIntoMem& operator = (const LoadFileIntoMem&) = delete;

    ~LoadFileIntoMem() noexcept { Do_unload(); }

    void ReLoad(int fd) {
        Do_unload();
        ptr = Do_load(fd);
    }
    auto &get_buf_size() const noexcept { return *(static_cast<std::size_t*>(ptr) - 1); }
  protected:
    static void* Do_load(int fd) {
        auto file_size{get_file_size(fd)};
        void *ret{static_cast<void*>(new char[file_size])};
        read_until_success(fd, ret, file_size);
        return ret;
    }
    void Do_unload() noexcept {
        delete static_cast<char*>(ptr);
        ptr = nullptr;
    }
};
}//namespace sort::impl

#endif
