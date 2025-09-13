#include "paulista/paulista-graph.hpp"
#include <set>
#include <algorithm>

namespace paulista {
namespace graph {
    std::optional<Nodal>
    nodal(std::size_t count, const domain::Elements& elements) {
        if (elements.empty()) { return std::nullopt; }

        using domain::element::Triangle;
        using domain::element::Tetrahedron;
        using domain::element::is_triangle;
        using domain::element::is_tetrahedron;

        std::vector<node::Indices> indices(count);
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

    std::optional<Dual>
    dual(const Nodal& nodal, const domain::Elements& elements, const Common& common) {
        if (elements.empty()) { return std::nullopt; }

        using domain::element::Triangle;
        using domain::element::Tetrahedron;
        using domain::element::is_triangle;
        using domain::element::is_tetrahedron;

        std::vector<node::Indices> adjacencies(elements.size());

        for (node::Index index = 0; index < elements.size(); index++) {
            const domain::Element& element = elements[index];
            std::set<node::Index> neighbors;

            node::Indices nodes = std::visit(visitor::nodes, element);

            for (node::Index node : nodes) {
                if (node >= nodal.indices.size()) { return std::nullopt; }
                for (node::Index neighbor : nodal.indices[node]) {
                    if (neighbor != index) { neighbors.insert(neighbor); }
                }
            }

            for (node::Index neighbor : neighbors) {
                if (neighbor < elements.size()) {
                    node::Indices other = std::visit(visitor::nodes, elements[neighbor]);

                    std::set<node::Index> intersection;
                    std::set_intersection(
                          nodes.begin()
                        , nodes.end()
                        , other.begin()
                        , other.end()
                        , std::inserter(intersection, intersection.begin())
                    );

                    if (intersection.size() >= std::visit(visitor::shared, common)) {
                        adjacencies[index].push_back(neighbor);
                    }
                }
            }

            std::sort(adjacencies[index].begin(), adjacencies[index].end());
        }

        return Dual{adjacencies};
    }
} // namespace graph
} // namespace paulista
