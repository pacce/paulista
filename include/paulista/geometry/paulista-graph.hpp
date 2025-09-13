#ifndef PAULISTA_GRAPH_HPP__
#define PAULISTA_GRAPH_HPP__

#include "paulista/paulista-domain.hpp"
#include <optional>
#include <vector>

namespace paulista {
namespace graph {
    struct Nodal {
        std::vector<std::size_t> indices;
    };
namespace nodal {
    std::optional<Nodal>
    construct(const domain::Elements& elements);
} // namespace nodal
} // namespace graph
} // namespace paulista

#endif // PAULISTA_GRAPH_HPP__
