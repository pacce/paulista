#include "paulista/paulista-sparse.hpp"
#include <numeric>

namespace paulista {
namespace sparse {
    std::optional<std::size_t>
    nonzero(const Graph& graph) {
        if (graph.empty()) { return std::nullopt; }

        std::size_t count = std::accumulate(
                  graph.adjacencies.begin()
                , graph.adjacencies.end()
                , 0
                , [](std::size_t acc, const graph::vertex::Indices& vs) {
                    return acc + vs.size();
                }
            );
        return count + graph.size();
    }
namespace coordinate {
    bool
    contains(const graph::vertex::Indices& indices, std::size_t entry) {
        return std::find(indices.begin(), indices.end(), entry) != indices.end();
    }

    coordinate::Map
    mapping(const Graph& graph) {
        std::size_t cols = graph.size();
        std::size_t rows = graph.size();

        std::size_t index = 0;
        coordinate::Map mapper;

        for (std::size_t col = 0; col < cols; col++) {
            std::vector<std::size_t> entries{col};
            for (std::size_t row = 0; row < rows; row++) {
                const graph::vertex::Indices& neighbors = graph[row];
                if (coordinate::contains(neighbors, col)) {
                    entries.push_back(row);
                }
            }
            std::sort(entries.begin(), entries.end());
            for (std::size_t entry : entries) {
                mapper[{entry, col}] = index++;
            }
        }
        return mapper;
    }
} // namespace coordinate
} // namespace sparse
} // namespace paulista
