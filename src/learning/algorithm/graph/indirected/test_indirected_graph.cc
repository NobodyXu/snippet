#include <iostream>
#include "indirected_graph.hpp"
using nxwheels::indirected_graph;

template <class Stream>
struct OutStreamAdaptor {
    Stream &&s;

    template <class T>
    auto& operator << (T &&t) { s << t << std::endl; return *this; }
};
template <class T> OutStreamAdaptor(T&&) -> OutStreamAdaptor<T&&>;


int main() {
    indirected_graph graph{};

    graph.fromStream(std::cin);
    graph.toStream(OutStreamAdaptor{std::cout});
}
