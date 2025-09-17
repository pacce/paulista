#ifndef PAULISTA_GRAPH_HPP__
#define PAULISTA_GRAPH_HPP__

#include "paulista/paulista-domain.hpp"
#include "paulista/paulista-element.hpp"

#include <list>
#include <optional>
#include <vector>
#include <compare>

namespace paulista {
namespace graph {
namespace node {
    using Index     = std::size_t;
    using Indices   = std::vector<Index>;
} // namespace node
namespace vertex {
    using Index     = std::size_t;
    using Indices   = std::vector<std::size_t>;
} // namespace vertex
namespace visitor {
    struct indices {
        node::Indices
        operator()(const element::Triangle& e) const {
            node::Indices nodes = {e.u, e.v, e.w};
            std::sort(nodes.begin(), nodes.end());
            return nodes;
        }

        node::Indices
        operator()(const element::Tetrahedron& e) const {
            node::Indices nodes = {e.u, e.v, e.w, e.z};
            std::sort(nodes.begin(), nodes.end());
            return nodes;
        }
    };

    constexpr indices nodes;
} // namespace visitor

namespace common {
    struct Point {};
    struct Edge {};
    struct Face {};
} // namespace common

    using Common = std::variant<common::Point, common::Edge, common::Face>;

namespace visitor {
    struct required {
        std::size_t operator()(const common::Point&) const { return 1; }
        std::size_t operator()(const common::Edge&)  const { return 2; }
        std::size_t operator()(const common::Face&)  const { return 3; }
    };

    constexpr required shared;
} // namespace visitor
    struct Nodal {
        std::vector<node::Indices> indices;
    };

    std::optional<Nodal>
    nodal(std::size_t count, const Elements& elements);

    // std::optional<Dual>
    // dual(const Nodal& nodal, const Elements& elements, const Common& common);
} // namespace graph
    struct Graph {
        std::vector<graph::vertex::Indices> adjacencies;

        bool empty() const;
        std::size_t size() const;

        graph::vertex::Indices& operator[](std::size_t index);
        const graph::vertex::Indices& operator[](std::size_t index) const;

        graph::vertex::Indices& at(std::size_t index);
        const graph::vertex::Indices& at(std::size_t index) const;
    };
namespace graph {
namespace node {
    std::optional<Graph>
    dual(const Elements& elements);
} // namespace node
namespace element {
    std::optional<Graph>
    dual(const Elements& elements, const Common& common);
} // namespace element
    struct Degree {
        std::size_t vertex;
        std::size_t value;

        bool operator<(const Degree& other) const;
        bool operator<=(const Degree& other) const;
        bool operator>(const Degree& other) const;
        bool operator>=(const Degree& other) const;
        bool operator==(const Degree& other) const;
        bool operator!=(const Degree& other) const;
        std::strong_ordering operator<=>(const Degree& other) const;

        friend std::ostream&
        operator<<(std::ostream& os, const Degree& degree);
    };

    std::optional<std::list<Degree>>
    degrees(const Graph& graph);

    using Ordering = std::size_t;

    std::optional<std::vector<Ordering>>
    ordering(const Graph& graph, std::list<Degree>& degrees);

    using Color = std::size_t;
namespace coloring {
namespace smallest {
    std::optional<std::vector<Color>>
    last(const Graph& graph);
} // namespace smallest
} // namespace coloring
} // namespace graph
} // namespace paulista

#endif // PAULISTA_GRAPH_HPP__
