#include "paulista/paulista-graph.hpp"
#include <set>
#include <algorithm>
#include <list>
#include <unordered_map>

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

    bool
    Dual::empty() const {
        return adjacencies.empty();
    }

    std::size_t
    Dual::size() const {
        return adjacencies.size();
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

    std::optional<std::vector<Color>>
    color(const Dual& dual) {
        if (dual.empty()) { return std::nullopt; }
        std::size_t count = dual.size();


        struct Entry {
            std::size_t degree;
            std::size_t vertex;

            bool operator<(const Entry& other) const {
                return degree < other.degree;
            }
        };

        std::list<Entry> entries;

        for (std::size_t i = 0; i < count; i++) {
            entries.push_back({dual.adjacencies[i].size(), i});
        }

        std::vector<std::size_t> ordering;
        ordering.reserve(count);

        while (not entries.empty()) {
            std::list<Entry>::iterator it = std::min_element(entries.begin(), entries.end());

            std::size_t vertex = it->vertex;
            ordering.push_back(vertex);
            entries.erase(it);

            for (Entry& entry : entries) {
                for (node::Index neighbor : dual.adjacencies[vertex]) {
                    if (entry.vertex == neighbor) { entry.degree--; break; }
                }
            }
        }

        std::vector<Color>                      colors(count, 0);
        std::unordered_map<std::size_t, Color>  processed;
        for (std::size_t i = count; i > 0; i--) {
            std::size_t vertex = ordering[i - 1];
            std::set<Color> used;

            for (node::Index neighbor : dual.adjacencies[vertex]) {
                if (processed.contains(neighbor)) {
                    used.insert(processed[neighbor]);
                }
            }

            Color color = 0;
            while (used.contains(color)) { color++; }

            processed[vertex]   = color;
            colors[vertex]      = color;
        }

        return colors;
    }
} // namespace graph
} // namespace paulista
