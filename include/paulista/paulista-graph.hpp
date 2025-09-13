#ifndef PAULISTA_GRAPH_HPP__
#define PAULISTA_GRAPH_HPP__

#include "paulista/paulista-domain.hpp"
#include <optional>
#include <vector>

namespace paulista {
namespace graph {
    struct Nodal {
        std::vector<std::vector<std::size_t>> indices;
    };

    std::optional<Nodal>
    nodal(std::size_t count, const domain::Elements& elements);
} // namespace graph
} // namespace paulista

#endif // PAULISTA_GRAPH_HPP__
