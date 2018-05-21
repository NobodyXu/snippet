    // C++17
    #include <benchmark/benchmark.h> // Googleo benchmark lib, for benchmark.

    #include <new>     // For std::bad_alloc.
    #include <memory>  // For std::allocator_traits, std::uninitialized_move.
    #include <cstdlib> // For C heap management API.
    #include <cstddef> // For std::size_t, std::max_align_t.
    #include <cassert> // For assert.
    #include <utility> // For std::forward, std::declval,
    #include <cstdint>

    namespace linux {
    #include <sys/mman.h> // For mmap, mremap, munmap.
    #include <errno.h>    // For errno.
    auto get_errno() noexcept {
        return errno;
    }
    }

    /*
     * Allocators.
     * These allocators will have non-standard compliant behavior if the type T's cp ctor has side effect.
     */

    // class mrealloc are usefull for allocating small space for
    // std::vector.
    //
    // Can prevent copy of data and memory fragmentation if there's enough
    // continous memory at the original place.
    template <class T>
    struct mrealloc {
        using pointer = T*;
        using value_type = T;

        auto allocate(std::size_t len) {
            if (auto ret = std::malloc(len))
                return static_cast<pointer>(ret);
            else
                throw std::bad_alloc();
        }
        auto reallocate(pointer old_ptr, std::size_t old_len, std::size_t len) {
            if (auto ret = std::realloc(old_ptr, len))
                return static_cast<pointer>(ret);
            else
                throw std::bad_alloc();
        }
        void deallocate(void *ptr, std::size_t len) noexcept {
            std::free(ptr);
        }
    };

    // class mmaprealloc is suitable for large memory use.
    //
    // It will be usefull for situation that std::vector can grow to a huge
    // size.
    //
    // User can call reserve without worrying wasting a lot of memory.
    //
    // It can prevent data copy and memory fragmentation at any time.
    template <class T>
    struct mmaprealloc {
        using pointer = T*;
        using value_type = T;

        auto allocate(std::size_t len) const
        {
            return allocate_impl(len, MAP_PRIVATE | MAP_ANONYMOUS);
        }
        auto reallocate(pointer old_ptr, std::size_t old_len, std::size_t len) const
        {
            return reallocate_impl(old_ptr, old_len, len, MREMAP_MAYMOVE);
        }
        void deallocate(pointer ptr, std::size_t len) const noexcept
        {
            assert(linux::munmap(ptr, len) == 0);
        }
      protected:
        auto allocate_impl(std::size_t _len, int flags) const
        {
            if (auto ret = linux::mmap(nullptr, get_proper_size(_len), PROT_READ | PROT_WRITE, flags, -1, 0))
                return static_cast<pointer>(ret);
            else
                fail(EAGAIN | ENOMEM);
        }
        auto reallocate_impl(pointer old_ptr, std::size_t old_len, std::size_t _len, int flags) const
        {
            if (auto ret = linux::mremap(old_ptr, old_len, get_proper_size(_len), flags))
                return static_cast<pointer>(ret);
            else
                fail(EAGAIN | ENOMEM);
        }

        static inline constexpr const std::size_t magic_num = 4096 - 1;
        static inline auto get_proper_size(std::size_t len) noexcept -> std::size_t {
            return round_to_pagesize(len);
        }
        static inline auto round_to_pagesize(std::size_t len) noexcept -> std::size_t {
            return (len + magic_num) & ~magic_num;
        }

        static inline void fail(int assert_val)
        {
            auto _errno = linux::get_errno();
            assert(_errno == assert_val);
            throw std::bad_alloc();
        }
    };

    template <class T>
    struct mmaprealloc_populate_ver: mmaprealloc<T> {
        auto allocate(size_t len) const
        {
            return mmaprealloc<T>::allocate_impl(len, MAP_PRIVATE | MAP_ANONYMOUS | MAP_POPULATE);
        }
    };

    namespace impl {
    struct disambiguation_t2 {};
    struct disambiguation_t1 {
        constexpr operator disambiguation_t2() const noexcept { return {}; }
    };
    template <class Alloc>
    static constexpr auto has_reallocate(disambiguation_t1) noexcept -> decltype(&Alloc::reallocate, bool{}) { return true; }
    template <class Alloc>
    static constexpr bool has_reallocate(disambiguation_t2) noexcept { return false; }
    template <class Alloc>
    static inline constexpr const bool has_reallocate_v = has_reallocate<Alloc>(disambiguation_t1{});
    } /* impl */

    template <class Alloc>
    struct allocator_traits: public std::allocator_traits<Alloc> {
        using Base = std::allocator_traits<Alloc>;
        using value_type = typename Base::value_type;
        using pointer = typename Base::pointer;
        using size_t = typename Base::size_type;

        static auto reallocate(Alloc &alloc, pointer prev_ptr, size_t prev_len, size_t new_len) {
            if constexpr(impl::has_reallocate_v<Alloc>)
                return alloc.reallocate(prev_ptr, prev_len, new_len);
            else {
                auto new_ptr = Base::allocate(alloc, new_len);

                // Move existing array
                for(auto _prev_ptr = prev_ptr, _new_ptr = new_ptr; _prev_ptr != prev_ptr + prev_len; ++_prev_ptr, ++_new_ptr) {
                    new (_new_ptr) value_type(std::move(*_prev_ptr));
                    _prev_ptr->~value_type();
                }
                Base::deallocate(alloc, prev_ptr, prev_len);

                return new_ptr;
            }
        }
    };

    template <class T, class Alloc = std::allocator<T>>
    struct vector: protected Alloc {
        using alloc_traits = allocator_traits<Alloc>;
        using pointer = typename alloc_traits::pointer;
        using size_t = typename alloc_traits::size_type;
        pointer ptr = nullptr;
        size_t last = 0;
        size_t avail = 0;

        ~vector() {
            alloc_traits::deallocate(*this, ptr, avail);
        }

        template <class ...Args>
        void emplace_back(Args &&...args) {
            if (last == avail)
                double_the_size();
            alloc_traits::construct(*this, &ptr[last++], std::forward<Args>(args)...);
        }
        void double_the_size() {
            if (__builtin_expect(!!(avail), true)) {
                avail <<= 1;
                ptr = alloc_traits::reallocate(*this, ptr, last, avail);
            } else {
                avail = 1 << 4;
                ptr = alloc_traits::allocate(*this, avail);
            }
        }
    };

    template <class T>
    static void BM_vector(benchmark::State &state) {
        for(auto _: state) {
            T c;
            for(auto i = state.range(0); --i >= 0; )
                try {
                    c.emplace_back((char)i);
                } catch(std::bad_alloc e) {
                    state.SkipWithError(e.what());
                }
        }
    }

    static constexpr const auto one_GB = 1 << 30;

    BENCHMARK_TEMPLATE(BM_vector, vector<char>)                                         ->Range(1 << 3, one_GB / 8);
    BENCHMARK_TEMPLATE(BM_vector, vector<std::uint64_t, mrealloc<std::uint64_t>>)                ->Range(1 << 3, one_GB / 8);
    BENCHMARK_TEMPLATE(BM_vector, vector<std::uint64_t, mmaprealloc<std::uint64_t>>)             ->Range(1 << 3, one_GB / 8);
    BENCHMARK_TEMPLATE(BM_vector, vector<std::uint64_t, mmaprealloc_populate_ver<std::uint64_t>>)->Range(1 << 3, one_GB / 8);
    BENCHMARK_MAIN();
