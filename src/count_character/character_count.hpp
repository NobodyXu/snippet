#include <algorithm>

#include <cassert>
#include <utility>
#include <type_traits>

// Definition of helper functions for converting ints to string(raw and no need for format string).

template <class size_t, class UnsignedInt,
          class = std::enable_if_t<std::is_unsigned<UnsignedInt>::value>>
size_t to_str_len(UnsignedInt i) noexcept
{
    size_t cnt = 0;

    do {
        ++cnt;
        i /= 10;
    } while (i > 0);

    return cnt;
}

/*
 * out should either points to the beginning of array   or the last.
 * step should be either 1 or -1.
 */
template <class RandomAccessIt, class UnsignedInt,
          class = std::enable_if_t<std::is_unsigned<UnsignedInt>::value>>
auto uitos_impl(RandomAccessIt out, int step, UnsignedInt i) noexcept
{
    do {
        *out = static_cast<char>(i % 10) + 48;
        out += step;
        i /= 10;
    } while (i > 0);

    return out;
}

template <class BidirectionalIt>
void reverse_str(BidirectionalIt beg, BidirectionalIt end) noexcept
{
    do {
        std::iter_swap(beg++, --end);
    } while (beg < end);
}

template <class RandomAccessIt, class UnsignedInt>
auto uitos(RandomAccessIt beg, UnsignedInt i) noexcept
{
    auto ret = uitos_impl(beg, 1, i);

    // Reverse the string to get the right order
    reverse_str(beg, ret);

    return ret;
}

template <class RanIt, class UnsignedInt>
auto r_uitos(RanIt last, UnsignedInt i) noexcept
{
    return uitos_impl(last, -1, i);
}

template <class size_t, class RandomAccessIt>
size_t count_repeat(RandomAccessIt beg, RandomAccessIt end) noexcept
{
    auto first = beg;
    auto &val = *beg;
    do {
        ++beg;
    } while (beg != end && *beg == val);

    return beg - first;
}

template <class size_t, class RandomAccessIt>
size_t r_count_repeat(RandomAccessIt last) noexcept
{
    auto it = last;
    auto &val = *it;
    do {
        --it;
    } while (*it == val);

    return last - it;
}

template <class string,
          class size_type = typename string::size_type>
struct character_count
{
    static_assert(std::is_unsigned<size_type>::value,
                     "size_type should be unsigned");
    static_assert(!std::is_empty<size_type>::value,
                     "size_type should not be empty");

private:
    using str_size_t = typename string::size_type;
    using str_it = typename string::iterator;

    static_assert(std::is_same<typename string::value_type, char>::value,
                     "Only support ASCII");
    static_assert(sizeof(size_type) <= sizeof(str_size_t),
                     "size_type should not be bigger than typename string::size_type");


    string str;

    str_it in;
    str_it out;
    str_it end;
    size_type len;

    void cnt_repeat() noexcept
    {
        assert(in != end);
        len = count_repeat<size_type>(in, str.end());
    }

    void advance_in() noexcept
    {
        assert(in != end);
        in += len;
        assert(in <= end);
    }

    void process_impl()
    {
        assert(in != end);
        assert(out <= in);

        // The main loop
        do {
            cnt_repeat();
            if (len > 1 || out < in) {
                *out = *in;
                out = uitos(out + 1, len);

                advance_in();

                assert(out <= in);
            } else {
	            auto first = find_enough_space();
		        auto deduced_first = write_backward();

		        assert(first == deduced_first);
	        }
        } while (in != end);
    }

    auto find_enough_space()
    {
        assert(out == in);

        auto first = in;
        size_type bytes_required = 0;

        do {
            cnt_repeat();

            advance_in();
            bytes_required += to_str_len<size_type>(len) + 1;

            if (size_type(in - first) >= bytes_required) {
                out = first + bytes_required;
                return first;
            }
        } while (in != str.end());

        auto first_offset = first - str.begin();
        // Hopefully this path won't be executed.
        auto new_size = first_offset + bytes_required;
	    
        auto original_size = str.size();
        assert(new_size > original_size);
        
        str.resize(new_size);
    
        first = str.begin() + first_offset;
        out = str.end();
        in = str.begin() + original_size;
        end = str.begin() + original_size;

	    return first;
    }

    auto write_backward() noexcept
    {
        auto original_out = out--;
	    auto original_in = in--;

        do {
	        len = r_count_repeat<size_type>(in);

            out = r_uitos(out, len);
            *out-- = *((in -= len) + 1);
        } while (out != in);

	   auto ret = out + 1;

	   out = original_out;
	   in = original_in;

	   return ret;
    }

public:
    character_count(string &&arg):
        str(std::move(arg)), in(str.begin()), out(str.begin()), end(str.end())
    {}

    character_count(const string &arg):
        str(arg), in(str.begin()), out(str.begin()), end(str.end())
    {}

    /*
        * ```str``` should not be empty and should not have non-visible character
        */
    auto& process()
    {
        assert(!str.empty());
        process_impl();

        str.erase(out, str.end());

        return *this;
    }

    auto& get_result() & noexcept
    {
        return str;
    }
    auto&& get_result() && noexcept
    {
        return std::move(str);
    }
    auto& get_result() const& noexcept
    {
        return str;
    }

    auto& set_string(const string &arg) noexcept
    {
        str = arg;

        in = str.begin();
        out = str.begin();
        end = str.end();

        return *this;
    }
    auto& set_string(string &&arg) noexcept
    {
        str = std::move(arg);

        in = str.begin();
        out = str.begin();
        end = str.end();

        return *this;
    }
};
