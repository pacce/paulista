#include "paulista/paulista-graph.hpp"

namespace paulista {
namespace graph {
    std::optional<Nodal>
    nodal(std::size_t count, const domain::Elements& elements) {
        if (elements.empty()) { return std::nullopt; }

        using domain::element::Triangle;
        using domain::element::Tetrahedron;
        using domain::element::is_triangle;
        using domain::element::is_tetrahedron;

        std::vector<std::vector<std::size_t>> indices(count);
        for (std::size_t i = 0; i < elements.size(); i++) {
            const domain::Element& element = elements[i];
            if (std::visit(is_triangle, element)) {
                Triangle e = std::get<Triangle>(element);
                if (e.u > indices.size()) { return std::nullopt; }
                if (e.v > indices.size()) { return std::nullopt; }
                if (e.w > indices.size()) { return std::nullopt; }

                indices[e.u].push_back(i);
                indices[e.v].push_back(i);
                indices[e.w].push_back(i);
            } else if (std::visit(is_tetrahedron, element)) {
                Tetrahedron e = std::get<Tetrahedron>(element);
                if (e.u > indices.size()) { return std::nullopt; }
                if (e.v > indices.size()) { return std::nullopt; }
                if (e.w > indices.size()) { return std::nullopt; }
                if (e.z > indices.size()) { return std::nullopt; }

                indices[e.u].push_back(i);
                indices[e.v].push_back(i);
                indices[e.w].push_back(i);
                indices[e.z].push_back(i);
            }
        }

        for (std::vector<std::size_t>& index : indices) {
            std::sort(index.begin(), index.end());
        }
        return Nodal{indices};
    }
} // namespace graph
} // namespace paulista
