#ifndef  __snake_container_dynamic_bitset_HPP__
# define __snake_container_dynamic_bitset_HPP__

# include "../expect.h"

# include <cstdlib>
# include <new>
# include <memory>

namespace container {
/*!
 * dynamic_bitset can only work on little-endian machines.
 * The alignment of the bitset is promised to be zero.
 *
 * Invariant: data() != 0, size() != 0, size() <= allocated_size()
 *
 * If size() == 0, then data() == 0, std::bad_alloc will be thrown.
 */
class dynamic_bitset
{
    using self = dynamic_bitset;

    const std::unique_ptr<unsigned char[]> bitset_p;
    const std::size_t bits;

    /*!
     * precondition: bits > 0
     */
    static auto get_size_for_allocation(std::size_t bits) noexcept
    {
	// Convert and align bits into bytes  
	std::size_t bytes = bits / 8;

	if (bits % 8)
	    ++bytes;

	return bytes;
    }

    /*!
     * precondition: bits > 0
     *
     * allocate_bitset(std::size_t) returns a pointer to zero-initialized memory on heap.
     * If allocation fails, std::bad_alloc will be thrown.
     */
    static auto* allocate_bitset(std::size_t bits)
    {
	/*
	 * calloc will zero-initialized the memory, either by calloc itself or by the syscall mmap.
	 * If latter happens, the lazy allocation scheme used by linux kernel can help saving memory.
	 */
	auto *ret = static_cast<unsigned char*>(calloc(sizeof(char), get_size_for_allocation(bits)));

	if (unlikely(ret == nullptr))
	    throw std::bad_alloc();

	return ret;
    }

public:
    using size_type = std::size_t;

    /*!
     * precondition: bits_arg > 0
     */
    dynamic_bitset(size_type bits_arg): 
	bitset_p{allocate_bitset(bits_arg)}, bits{bits_arg}
    {}

    dynamic_bitset(const self&) = delete;
    dynamic_bitset(self&&) = delete;

    self& operator = (const self&) = delete;
    self& operator = (self&&) = delete;

    ~dynamic_bitset() = default;

    /*!
     * size() returns the number of bits allocated, excluding the bits used for alignment.
     */
    size_type size() const noexcept
    {
	return bits;
    }

    size_type allocated_size() const noexcept
    {
	return get_size_for_allocation(bits);
    }

    bool get(size_type pos) const noexcept
    {
	return (bitset_p[pos / 8] >> (7 - pos % 8)) & 1;
    }

    void set(size_type pos) noexcept
    {
	(bitset_p[pos / 8]) |= (1 << (7 - pos % 8));
    }

    /*!
     * precondition: get(pos) == true
     */
    void unset(size_type pos) noexcept
    {
	(bitset_p[pos / 8]) -= (1 << (7 - pos % 8));
    }

    auto data() const noexcept
    {
	return const_cast<const unsigned char*>(bitset_p.get());
    }

    /*!
     * touch(size_type) is equivalent to data()[pos / 8].
     */
    void touch(size_type pos) const noexcept
    {
	*static_cast<const volatile unsigned char*>(&bitset_p[pos / 8]);
    }
};
} /* namespace container */
#endif
