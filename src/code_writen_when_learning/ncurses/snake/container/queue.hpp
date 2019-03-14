#ifndef  __snake_container_queue_HPP__
# define __snake_container_queue_HPP__

# include "../expect.h"

# include <forward_list>
# include <list>
# include <iterator>

# include <cstdlib>
# include <memory>

# include <stdexcept>
# include <utility>
# include <type_traits>
# include <cstddef>

namespace container::impl {
class queue_base
{
protected:
    const std::size_t len_per_block;
    const std::size_t sizeof_each_var;

    queue_base(std::size_t len_per_block_arg, std::size_t sizeof_each_var_arg):
	len_per_block{len_per_block_arg}, sizeof_each_var{sizeof_each_var_arg}
    {
	if (unlikely(sizeof_each_var == 0	     ||
		     len_per_block   == 0	     ||
		     len_per_block % sizeof_each_var != 0))
	    throw std::invalid_argument{"Invalid argument in typeless_ForwardListOfArray_base ctor"};
    }
};

template <class Container>
struct emplace_after_impl_class
{
    using iterator = typename Container::iterator;

    template <class ...Args>
    static void f(Container &c, iterator &last, Args &&...args)
    {
	auto last_offset = std::distance(last, c.begin());

	c.emplace_back(std::forward<Args>(args)...);

	last = c.begin();
	std::advance(last, last_offset);
    }
};

template <class T, class Alloc>
struct emplace_after_impl_class<std::list<T, Alloc>>
{
    using Container = std::list<T, Alloc>;
    using iterator = typename Container::iterator;

    template <class ...Args>
    static void f(Container &c, iterator &last, Args &&...args)
    {
	c.emplace(std::next(last), std::forward<Args>(args)...);
    }
};

template <class T, class Alloc>
struct emplace_after_impl_class<std::forward_list<T, Alloc>>
{
    using Container = std::forward_list<T, Alloc>;
    using iterator = typename Container::iterator;

    template <class ...Args>
    static void f(Container &c, iterator &last, Args &&...args)
    {
	c.emplace_after(last, std::forward<Args>(args)...);
    }
};

template <class Container, class ...Args>
void emplace_after(Container &c, typename Container::iterator &last, Args &&...args)
{
    static_assert(std::is_const<Container>::value == false);
    static_assert(std::is_volatile<Container>::value == false);

    emplace_after_impl_class<Container>::f(c, last, std::forward<Args>(args)...);
}

template <class Container>
struct move_first_to_unused_impl_class
{
    using iterator = typename Container::iterator;
    using value_type = typename Container::value_type;
    
    static void f(Container &c, iterator &last)
    {
	auto it = c.begin();
	auto last_offset = std::distance(c.begin(), last) - 1;

	value_type tmp = std::move(*it);
	c.erase(it);

	last = c.begin();
	std::advance(last, last_offset);
	c.emplace(std::next(last), std::move(tmp));

	last = c.begin();
	std::advance(last, last_offset);
   }
};

template <class T, class Alloc>
struct move_first_to_unused_impl_class<std::list<T, Alloc>>
{
    using Container = std::list<T, Alloc>;
    using iterator = typename Container::iterator;
    
    static void f(Container &c, iterator &last) noexcept
    {
	c.splice(std::next(last), c, c.begin());
    }
};

template <class T, class Alloc>
struct move_first_to_unused_impl_class<std::forward_list<T, Alloc>>
{
    using Container = std::forward_list<T, Alloc>;
    using iterator = typename Container::iterator;
    
    static void f(Container &c, iterator &last) noexcept
    {
	c.splice_after(last, c, c.before_begin());
    }
};

/*!
 * move_first_to_unused moves the *c.begin() to become the first of the unused blocks and update last.
 */
template <class Container, class iterator = typename Container::iterator>
void move_first_to_unused(Container &c, iterator &last)
{
    static_assert(std::is_const<Container>::value == false);
    static_assert(std::is_volatile<Container>::value == false);

    move_first_to_unused_impl_class<Container>::f(c, last);
}
} /* container::impl */

namespace container {
/*!
 * queue is a type-erased container.
 *
 * It stores elements in a forward list of fix-sized array, each array along with the list
 * pointer is called 'block'. Memory can only be allocated and deallocated in blocks.
 *
 * It is capable of automatically reuse freed block and append them at the end of the 
 * occupied list (to improve cache locality).
 *         last block (where last_list_p points to), freed blocks
 *
 * In order to improve cache locality, the blocks that are unused will be append to the last 
 * block.
 *
 * Since the queue is only to be larger in the long run, there is no member function to free 
 * blocks except the dtor.
 */
template <template <class...> class Container>
class queue: private impl::queue_base
{
    using self = queue;
    using base = impl::queue_base;
    using Container_t = Container<std::unique_ptr<char[]>>;

    Container_t c;
    /* The last block which contains data, after it is the unused reserved blocks */
    typename Container_t::iterator last;

    /* Offset of beg/end of data, in byte */
    std::size_t beg_of_data_offset = 0;
    std::size_t end_of_data_offset = 0;

    /*
     * num_of_unused_blocks records the number of blocks that have no data on them.
     * num_of_unused_blocks + num_of_used_blocks == all blocks
     */
    std::size_t num_of_used_blocks = 0;
    std::size_t num_of_unused_blocks = 0;

    /*!
     * allocate_new_list allocate a new list and fill it with zero.
     * It will return nullptr if allocation fail.
     */
    void* allocate_new_block() const noexcept
    {
	return std::calloc(block_size(), sizeof(char));
    }

    void* Allocate_new_block() const
    {
	auto *new_block_p = allocate_new_block();

	if (unlikely(new_block_p == nullptr))
	    throw std::bad_alloc();

	return new_block_p;
    }

    auto begin_of_data()       noexcept -> char*
    {
	return &(*c.begin()[beg_of_data_offset]);
    }

    auto begin_of_data() const noexcept -> const char*
    {
	return static_cast<const char*>(&(*c.begin()[beg_of_data_offset]));
    }

    auto end_of_data()	     noexcept -> char*
    {
	return &((*last)[end_of_data_offset]);
    }

    auto end_of_data() const noexcept -> const char*
    {
	return static_cast<const char*>(&((*last)[end_of_data_offset]));
    }

public:
    using size_type = std::size_t;

    // For the sake of simplicity, any API that this project won't use will not be defined.
    queue() = delete;

    queue(const self&) = delete;
    queue(self&&) = delete;

    self& operator = (const self&) = delete;
    self& operator = (self&&) = delete;

    /*!
     * precondition: n != 0, len_per_block_arg != 0, sizeof_each_var_arg != 0, 
     *		     len_per_block_arg % sizeof_each_var_arg == 0
     *
     * queue(size_type, size_type, size_type)
     *     Allocate n * sizeof_element() / block_size() blocks.
     */
    queue(size_type n, size_type len_per_block_arg, size_type sizeof_each_var_arg):
	base{len_per_block_arg, sizeof_each_var_arg}, c(n * sizeof_each() / block_size())
    {
	if (unlikely(n == 0))
	    throw std::invalid_argument{"Invalid argument n in typeless_ForwardListOfArray ctor"};

	for (auto &block_unique_p: c)
	    block_unique_p.reset(Allocate_new_block());

	last = c.begin();
	num_of_unused_blocks = n * sizeof_each() / block_size();
    }

    bool is_empty() const noexcept
    {
	return begin_of_data() == end_of_data();
    }

    /*!
     * size() returns the number of initialized elements in the container.
     */
    auto size() const noexcept -> size_type
    {
	return ((num_of_used_blocks - 1) * block_size() + 
	        /* the size of initialized in the first block is calculated in byte */
	        (block_size() - beg_of_data_offset) - 
	        /* the size of uninitialized in the last block is calculated in byte */
	        (end_of_data_offset)
	       /* then divied by size of the element in bytes */
	       ) / sizeof_each();
    }

    /*!
     * capacity() returns the number of elements that the container is currently capable 
     * of holding (excluding the space that push_back() cannot use, that is, the space
     * created by pop_front() in the first block).
     */
    auto capacity() const noexcept -> size_type
    {
	return size() + 
	       (
		/* the size of uninitialized in the last block in byte */
	        (block_size() - end_of_data_offset) +
		/* the size of unused blocks in byte */
	        num_of_unused_blocks * block_size()
	       ) / sizeof_each();
    }

    auto block_size() const noexcept -> size_type
    {
	return len_per_block;
    }
    
    auto sizeof_each() const noexcept -> size_type
    {
	return sizeof_each_var;
    }

    void check_invariant() const
    {
	if (last == c.end())
	    goto throw_eception;
	if (beg_of_data_offset >= block_size() - sizeof_each())
	    goto throw_eception;
	if (end_of_data_offset >= block_size() - sizeof_each())
	    goto throw_eception;
	if (c.begin() == last && beg_of_data_offset > end_of_data_offset)
	    goto throw_eception;

	return;
throw_exception:
	    throw std::logic_error{"class invariant of typeless_ForwardListOfArray is brokwn"};
    }

    /*!
     * precondition: check_invariant()
     *
     * If capacity() == size() + sizeof_each(), append a new block at the end.
     * reserve_for_next_push_back() should be called before push_back().
     */
    void reserve_for_next_push_back(size_type new_cap)
    {
	if (unlikely(block_size() - end_of_data_offset == sizeof_each() && num_of_unused_blocks == 0)) {
	    impl::emplace_after(c, last, std::unique_ptr<char[]>{Allocate_new_block()});
	    ++num_of_unused_blocks;
	}
    }

    auto front()       noexcept -> char&
    {
	return *begin_of_data();
    }

    auto front() const noexcept -> const char&
    {
	return *begin_of_data();
    }

    /*!
     * precondition: is_empty() == false, check_invariant() does not throw
     *
     * pop_front() does not check precondition.
     */
    void pop_front() noexcept
    {
	if (unlikely(beg_of_data_offset + sizeof_each() == block_size())) {
	    impl::move_first_to_unused(c, last);
	    beg_of_data_offset = 0;

	    --num_of_used_blocks;
	    ++num_of_unused_blocks;
	} else {
	    beg_of_data_offset += sizeof_each();
	}
    }

    /*!
     * precondition: num_of_unused_blocks != 0 (can be ensured by calling reserve_for_next_push_back())
     *
     * push_back_noexcept(void*) does not check precondition or not and thus
     * reserve_for_next_push_back() should be called before calling this function.
     *
     * It is an optimization for cases which memory allocation cannot happens in critical code path.
     */
    void push_back_noexcept(char *ptr) noexcept
    {
	/*
	 * copy data from ptr to the block 
	 * Since it will be pretty small (below 16 bytes), use memcpy will be a waste.
	 */
	for (std::size_t i = 0; i != sizeof_each(); ++i)
	    end_of_data()[i] = ptr[i];

	if (unlikely(end_of_data_offset + sizeof_each() == block_size())) {
	    ++last;
	    end_of_data_offset = 0;

	    ++num_of_used_blocks;
	    --num_of_unused_blocks;
	} else {
	    end_of_data_offset += sizeof_each();
	}
    }

    /*!
     * precondition: check_invariant()
     *
     * touch_back() accesses the next memory push_back() will use to improve cache locality and prevent
     * page misses on critical path.
     */
    void touch_back() const noexcept
    {
	// A simplified version
	char *beg = end_of_data(), *end = beg + sizeof_each(); 
	do {
	    *static_cast<const volatile char*>(beg);
	    ++beg;
	} while (beg != end);
    }

    ~queue() = default;
};
} /* container */
#endif
