#ifndef PAULISTA_GRAPH_HPP__
#define PAULISTA_GRAPH_HPP__

#include "paulista/paulista-domain.hpp"
#include <optional>
#include <vector>

namespace paulista {
namespace graph {
namespace node {
    using Index     = std::size_t;
    using Indices   = std::vector<Index>;
} // namespace node

namespace visitor {
    struct indices {
        node::Indices operator()(const domain::element::Triangle& e) const {
            node::Indices nodes = {e.u, e.v, e.w};
            std::sort(nodes.begin(), nodes.end());
            return nodes;
        }

        node::Indices operator()(const domain::element::Tetrahedron& e) const {
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

    struct Dual {
        std::vector<node::Indices> adjacencies;
    };

    std::optional<Nodal>
    nodal(std::size_t count, const domain::Elements& elements);

    std::optional<Dual>
    dual(const Nodal& nodal, const domain::Elements& elements, const Common& common);
} // namespace graph
} // namespace paulista

#endif // PAULISTA_GRAPH_HPP__
