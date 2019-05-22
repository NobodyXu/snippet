#include "path.hpp"
using namespace nxwheels;

#include <cassert>

int main() {
    // Test path_basic with _Index_t = int;
    {
        // Test usr-defined ctor.
        path_basic<int> p{1};

        // Test is_marked and mark.
        assert(!p.is_marked(0));
        p.mark(0);
        assert(p.is_marked(0));

        assert(!p.is_marked(10));
        p.mark(10);
        assert(p.is_marked(10));
    }

    // Test path_advanced with _Index_t = int;
    {
        using path = path_advanced<unsigned>;
        using Index_t = typename path::Index_t;

        // Test Index_t first. The correctness of path_advanced rely on Index_t.
        // Compile-time test.
        {
            // Test inherited ctors.
            static_assert(std::is_constructible<Index_t, const Index_t&>{}());
            static_assert(std::is_constructible<Index_t,       Index_t&&>{}());

            // Test converting ctors.
            static_assert(std::is_constructible<Index_t, unsigned char>{}());
            static_assert(std::is_constructible<Index_t, u8>{}());

            // Test overloaded ctors.
            static_assert(std::is_constructible<Index_t>{}());
            static_assert(std::is_constructible<Index_t, unsigned>{}());
        }
        // Test placeholder_v and max_v. The runtime test assumes they are true.
        {
            static_assert(path::placeholder_v == std::numeric_limits<unsigned>::max());
            static_assert(path::max_v         == std::numeric_limits<unsigned>::max() - 1);
        }
        // Runtime test.
        {
            path p{make_Int<Index_t>(2)};

            assert(!p.is_marked(make_Int<Index_t>(0)));
            assert(!p.is_marked(make_Int<Index_t>(1)));
            assert(!p.is_marked(make_Int<Index_t>(2)));

            // Initialize root node.
            p.mark({make_Int<Index_t>(0), make_Int<Index_t>(0)});
            assert(p.is_marked(make_Int<Index_t>(0)));

            p.mark({make_Int<Index_t>(0), make_Int<Index_t>(10)});
            assert(p.is_marked(make_Int<Index_t>(10)));

            // Test PathTo.
            for (auto &node: p.PathTo(make_Int<Index_t>(10)))
                assert(node == make_Int<Index_t>(10));
        }
    }
}
