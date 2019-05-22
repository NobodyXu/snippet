#ifndef __nobodyxu_wheels_indirected_search_HPP__
# define __nobodyxu_wheels_indirected_search_HPP__

# include <utility>
# include <cassert>

# include "indirected_graph.hpp"
# include "../../range/range.hpp"
# include "path.hpp"

namespace nxwheels::id_graph {
template <class Index_t, class const_it_beg, class const_it_end>
struct nodes_group {
    Index_t from;
    range<const_it_beg, const_it_end> rng;
};

template <class Graph, template <class...> class Template_Path, template <class...> class Template_Recorder>
class Search_t {
    using const_graph_it_beg = decltype(std::declval<Graph>.adj(typename Graph::Index_t{}).begin());
    using const_graph_it_end = decltype(std::declval<Graph>.adj(typename Graph::Index_t{}).end());
public:
    using Path     = Template_Path    <typename Graph::Index_t>;
    using Index_t  = typename Path::Index_t;
    using Recorder = Template_Recorder<nodes_group<Index_t, const_graph_it_beg, const_graph_it_end>>;

    const Graph &g;
    Index_t root;
    Path path;
    Recorder recorder;

    constexpr Search_t(const Graph &arg_g, const Index_t &arg_root) noexcept : g{arg_g}, root{arg_root} {
        assert(g.V() <= Path::max_v.get_value());
    }
private:
    struct iterator_end {};
    struct iterator_beg: public input_iterator_base<iterator_beg> {
        using value_type      = std::pair<Index_t, bool>;
        using reference       = value_type;
        using pointer         = value_type*;
        using difference_type = Index_t;
        using iterator_category = std::input_iterator_tag;
    private:
        Search_t *data;
        decltype(std::declval<Recorder>().topIt()) top;

        void addChilds(Index_t &from) noexcept {
            if (const auto &to_ids = data->g.adj(from); !to_ids.empty()) {
                if constexpr(Path::record_path)
                    recorder.emplace(from, to_ids);
                else
                    recorder.emplace(to_ids);
            }
        }
    public:
        constexpr iterator_beg(Search_t *arg_data): data{arg_data} {
            if constexpr(Path::record_path)
                data->path.mark({data->root, data->root});
            else
                data->path.mark(data->root);

            addChilds(root);
        }

        constexpr reference operator * () {
            top = recorder.topIt();
            auto &to = *top->rng.begin();
            bool not_marked = !path.is_marked(*top->rng.begin());

            if (not_marked) {
                if constexpr(Path::record_path)
                    path.mark({top->from, to});
                else
                    path.mark(to);

                addChilds(to);
            }

            return {to, not_marked};
        }
        constexpr auto& operator ++ () {
            ++top->rng.begin();
            return *this;
        }
        constexpr bool operator == (const iterator_end&) const noexcept {
            if (top->rng.begin() == top->rng.end()) {
                recorder.underlying_container.erase(top);

                if (recorder.empty())
                    return false;
            }
            return true;
        }
    };
public:
    iterator_beg begin() noexcept { return {this}; }
    iterator_end end()   noexcept { return {}; }
};

/*
template <class Derived_impl, class _Index_t, class Path, class Recorder>
void search(const indirected_graph_api<Derived_impl, _Index_t> &g, Path &&path, Recorder &&recorder, typename Path::Index_t root) {
    using Index_t = typename Path::Index_t;

    using const_it_beg = decltype(g.adj(Index_t{}).begin());
    using const_it_end = decltype(g.adj(Index_t{}).end());
    if constexpr(Path::record_path)
        static_assert(std::is_same<typename Recorder::value_type, nodes_group<Index_t, const_it_beg, const_it_end>>{}());
    else
        static_assert(std::is_same<typename Recorder::value_type, range<const_it_beg, const_it_end>>{}());

    if constexpr(std::is_unsigned<underlying_type<_Index_t>>{}())
        assert(g.V() <= Path::max_v.get_value());

    if constexpr(Path::record_path)
        path.mark({root, root});
    else
        path.mark(root);
    if (const auto &to_ids = g.adj(root); !to_ids.empty()) {
        if constexpr(Path::record_path)
            recorder.emplace(root, to_ids);
        else
            recorder.emplace(to_ids);
    } else
        return;

    while(true) {
        auto top = recorder.topUnderlyingIt();

        if (!path.is_marked(*top->rng.begin())) {
            if constexpr(Path::record_path)
                path.mark({top->from, *top->rng.begin()});
            else
                path.mark(*top->rng.begin());

            if (const auto &to_ids2 = g.adj(*top->rng.begin()); !to_ids2.empty()) {
                if constexpr(Path::record_path)
                    recorder.emplace(*top->rng.begin(), to_ids2);
                else
                    recorder.emplace(to_ids2);
            }
        }

        if (++top->rng.begin() == top->rng.end()) {
            recorder.underlying().erase(top);

            if (recorder.empty())
                break;
        }
    }
}
*/
    /*
        while(true) {
            auto &top = recorder.top();

            // Recurring.
            if (!path.is_marked(*top.rng.begin())) {
                path.mark({top.from, *top.rng.begin()});

                // Add all its child nodes to the recorder.
                if (const auto &to_ids2 = g.adj(*top.rng.begin()); !to_ids2.empty())
                    recorder.emplace(*top.rng.begin(), to_ids2);
            } else // Returning
                while (++top.rng.begin() == top.rng.end())
                    if (recorder.pop().empty())
                        return;
        }
        */
        /*
        while(true)
            if (auto &top = recorder.top(); !path.is_marked(*top.rng.begin())) {
                path.mark({top.from, *top.rng.begin()});
                const auto &to_ids2 = g.adj(*top.rng.begin());

                switch ((int(++top.rng.begin() == top.rng.end() && recorder.pop().empty()) << 1) | int(to_ids2.empty())) {
                default:
                    assert(false);
                case 3:
                    return;
                case 0:
                case 2:
                    // Add all its child nodes to the recorder.
                    recorder.emplace(*top.rng.begin(), to_ids2);
                case 1: ;
                }
            } else if (++top.rng.begin() == top.rng.end() && recorder.pop().empty())
                return;
        */
} /* nxwheels::id_graph */
#endif
