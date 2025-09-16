#include "paulista/paulista-sparse.hpp"
#include <numeric>

namespace paulista {
namespace sparse {
    std::optional<std::size_t>
    nonzero(const Graph& graph) {
        if (graph.empty()) { return std::nullopt; }

        return std::accumulate(
                  graph.adjacencies.begin()
                , graph.adjacencies.end()
                , 0
                , [](std::size_t acc, const graph::vertex::Indices& vs) {
                    return acc + vs.size();
                }
            );
    }
} // namespace sparse
} // namespace paulista
