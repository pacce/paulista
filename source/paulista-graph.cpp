#include "paulista/paulista-graph.hpp"

#include <algorithm>
#include <unordered_map>
#include <set>

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

    std::strong_ordering
    Degree::operator<=>(const Degree& other) const {
        return value <=> other.value;
    }

    bool
    Degree::operator<(const Degree& other) const {
        return (*this <=> other) < 0;
    }

    bool
    Degree::operator<=(const Degree& other) const {
        return (*this <=> other) <= 0;
    }

    bool
    Degree::operator>(const Degree& other) const {
        return (*this <=> other) > 0;
    }

    bool
    Degree::operator>=(const Degree& other) const {
        return (*this <=> other) >= 0;
    }

    bool
    Degree::operator==(const Degree& other) const {
        return (*this <=> other) == 0;
    }

    bool
    Degree::operator!=(const Degree& other) const {
        return (*this <=> other) != 0;
    }

    std::ostream&
    operator<<(std::ostream& os, const Degree& degree) {
        return os << std::format("({}, {})", degree.vertex, degree.value);
    }

    std::optional<std::list<Degree>>
    degrees(const Dual& dual) {
        if (dual.empty()) { return std::nullopt; }
        std::size_t count = dual.size();

        std::list<Degree> entries;
        for (std::size_t i = 0; i < count; i++) {
            entries.emplace_back(i, dual.adjacencies[i].size());
        }
        return entries;
    }

    std::optional<std::vector<Ordering>>
    ordering(const Dual& dual, std::list<Degree>& degrees) {
        if (dual.empty()) { return std::nullopt; }
        std::size_t count = dual.size();

        std::vector<Ordering> ordering;
        ordering.reserve(count);

        while (not degrees.empty()) {
            std::list<Degree>::iterator it = std::min_element(degrees.begin(), degrees.end());

            std::size_t vertex = it->vertex;
            ordering.push_back(vertex);
            degrees.erase(it);

            for (Degree& entry : degrees) {
                for (node::Index neighbor : dual.adjacencies[vertex]) {
                    if (entry.vertex == neighbor) { entry.value--; break; }
                }
            }
        }
        return ordering;
    }

    std::optional<std::vector<Color>>
    color(const Dual& dual) {
        if (dual.empty()) { return std::nullopt; }
        std::size_t count                               = dual.size();
        std::optional<std::list<Degree>> entries        = paulista::graph::degrees(dual);
        if (not entries)  { return std::nullopt; }
        std::optional<std::vector<Ordering>> ordering   = paulista::graph::ordering(dual, *entries);

        std::vector<Color>                      colors(count, 0);
        std::unordered_map<std::size_t, Color>  processed;
        for (std::size_t i = count; i > 0; i--) {
            std::size_t vertex = (*ordering)[i - 1];
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
