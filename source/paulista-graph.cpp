#include "paulista/paulista-graph.hpp"

#include <algorithm>
#include <unordered_map>
#include <set>
#include <iostream>

namespace paulista {
namespace graph {
    std::optional<Nodal>
    nodal(std::size_t count, const Elements& elements) {
        if (elements.empty()) { return std::nullopt; }

        using paulista::element::Triangle;
        using paulista::element::Tetrahedron;
        using paulista::element::is_triangle;
        using paulista::element::is_tetrahedron;

        std::vector<node::Indices> indices(count);
        for (std::size_t i = 0; i < elements.size(); i++) {
            const Element& element = elements[i];
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
} // namespace graph
    bool
    Graph::empty() const {
        return adjacencies.empty();
    }

    std::size_t
    Graph::size() const {
        return adjacencies.size();
    }

    graph::vertex::Indices&
    Graph::operator[](std::size_t index) {
        return adjacencies[index];
    }

    const graph::vertex::Indices&
    Graph::operator[](std::size_t index) const {
        return adjacencies[index];
    }

    graph::vertex::Indices&
    Graph::at(std::size_t index) {
        return adjacencies.at(index);
    }

    const graph::vertex::Indices&
    Graph::at(std::size_t index) const {
        return adjacencies.at(index);
    }
namespace graph {
namespace node {
    std::optional<Graph>
    dual(const Elements& elements) {
        if (elements.empty()) { return std::nullopt; }

        std::size_t count = 0;
        for (const Element& element : elements) {
            vertex::Indices vertices = std::visit(visitor::nodes, element);
            for (const vertex::Index& vertex : vertices) {
                count = std::max(vertex, count);
            }
        }

        std::vector<std::set<std::size_t>> adjacencies(count + 1);
        for (const Element& element : elements) {
            vertex::Indices vertices = std::visit(visitor::nodes, element);
            for (std::size_t i = 0    ; i < vertices.size(); i++) {
            for (std::size_t j = i + 1; j < vertices.size(); j++) {
                adjacencies[vertices[i]].insert(vertices[j]);
                adjacencies[vertices[j]].insert(vertices[i]);
            }
            }
        }

        Graph graph;
        graph.adjacencies.resize(count + 1);
        for (std::size_t i = 0; i <= count; i++) {
            graph.adjacencies[i].assign(adjacencies[i].begin(), adjacencies[i].end());
        }

        return graph;
    }
} // namespace node
namespace element {
    std::optional<Graph>
    dual(const Elements& elements, const Common& common) {
        if (elements.empty()) { return std::nullopt; }

        std::size_t count = 0;
        for (const Element& element : elements) {
            vertex::Indices vertices = std::visit(visitor::nodes, element);
            for (const vertex::Index& vertex : vertices) {
                count = std::max(vertex, count);
            }
        }
        std::optional<Nodal> nodal = graph::nodal(count + 1, elements);
        if (not nodal) { return std::nullopt; }

        using paulista::element::Triangle;
        using paulista::element::Tetrahedron;
        using paulista::element::is_triangle;
        using paulista::element::is_tetrahedron;

        std::vector<node::Indices> adjacencies(elements.size());

        for (node::Index index = 0; index < elements.size(); index++) {
            const Element& element = elements[index];
            std::set<node::Index> neighbors;

            node::Indices nodes = std::visit(visitor::nodes, element);

            for (node::Index node : nodes) {
                if (node >= nodal->indices.size()) { return std::nullopt; }
                for (node::Index neighbor : nodal->indices[node]) {
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

        return Graph{adjacencies};
    }
} // namespace element
    std::optional<std::list<Degree>>
    degrees(const Graph& graph) {
        if (graph.empty()) { return std::nullopt; }
        std::size_t count = graph.size();

        std::list<Degree> entries;
        for (std::size_t i = 0; i < count; i++) {
            entries.emplace_back(i, graph.adjacencies[i].size());
        }
        return entries;
    }

    std::optional<std::vector<Ordering>>
    ordering(const Graph& graph, std::list<Degree>& degrees) {
        if (graph.empty()) { return std::nullopt; }
        std::size_t count = graph.size();

        std::vector<Ordering> ordering;
        ordering.reserve(count);

        while (not degrees.empty()) {
            std::list<Degree>::iterator it = std::min_element(degrees.begin(), degrees.end());

            std::size_t vertex = it->vertex;
            ordering.push_back(vertex);
            degrees.erase(it);

            for (Degree& entry : degrees) {
                for (node::Index neighbor : graph.adjacencies[vertex]) {
                    if (entry.vertex == neighbor) { entry.value--; break; }
                }
            }
        }
        return ordering;
    }
namespace coloring {
namespace smallest {
    std::optional<std::vector<Color>>
    last(const Graph& graph) {
        if (graph.empty()) { return std::nullopt; }
        std::size_t count                               = graph.size();
        std::optional<std::list<Degree>> entries        = paulista::graph::degrees(graph);
        if (not entries)  { return std::nullopt; }
        std::optional<std::vector<Ordering>> ordering   = paulista::graph::ordering(graph, *entries);

        std::vector<Color>                      colors(count, 0);
        std::unordered_map<std::size_t, Color>  processed;
        for (std::size_t i = count; i > 0; i--) {
            std::size_t vertex = (*ordering)[i - 1];
            std::set<Color> used;

            for (node::Index neighbor : graph.adjacencies[vertex]) {
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
} // namespace smallest
} // namespace coloring
} // namespace graph
} // namespace paulista
