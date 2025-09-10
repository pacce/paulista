#ifndef PAULISTA_DOMAIN_HPP__
#define PAULISTA_DOMAIN_HPP__

#include <cmath>
#include <variant>
#include <type_traits>
#include "paulista-geometry.hpp"

namespace paulista {
namespace domain {
    template <typename Precision> using Node        = paulista::geometry::tridimensional::Point<Precision>;
    template <typename Precision> using Nodes       = std::vector<Node<Precision>>;

    template <typename Precision> using Centroid    = paulista::geometry::tridimensional::Point<Precision>;
    template <typename Precision> using Centroids   = std::vector<Node<Precision>>;
namespace element {
namespace visitor {
    template <typename T>
    struct is_element {
        template <typename U>
        bool operator()(const U&) const {
            return std::is_same_v<T, U>;
        }
    };
} // namespace visitor
    struct Triangle {
        std::size_t u;
        std::size_t v;
        std::size_t w;

        template <typename T>
        std::optional<Centroid<T>>
        centroid(const Nodes<T>& ns) const {
            if (u >= ns.size()) { return std::nullopt; }
            if (v >= ns.size()) { return std::nullopt; }
            if (w >= ns.size()) { return std::nullopt; }

            Nodes<T> ps = {ns[u], ns[v], ns[w]};
            return paulista::geometry::tridimensional::point::centroid(ps);
        }

        template <typename T>
        std::optional<T>
        area(const Nodes<T>& ns) const {
            if (u >= ns.size()) { return std::nullopt; }
            if (v >= ns.size()) { return std::nullopt; }
            if (w >= ns.size()) { return std::nullopt; }

            const Node<T>& p0 = ns[u];
            const Node<T>& p1 = ns[v];
            const Node<T>& p2 = ns[w];
            
            const Node<T> normal    = (p1 - p0).cross(p2 - p0);
            std::int32_t value      = static_cast<std::int32_t>(normal.dot(normal));

            return T(std::sqrt(value) / 2);
        }
    };

    struct Tetrahedron {
        std::size_t u;
        std::size_t v;
        std::size_t w;
        std::size_t z;

        template <typename T>
        std::optional<Centroid<T>>
        centroid(const Nodes<T>& ns) const {
            if (u >= ns.size()) { return std::nullopt; }
            if (v >= ns.size()) { return std::nullopt; }
            if (w >= ns.size()) { return std::nullopt; }
            if (z >= ns.size()) { return std::nullopt; }

            Nodes<T> ps = {ns[u], ns[v], ns[w], ns[z]};
            return paulista::geometry::tridimensional::point::centroid(ps);
        }
    };

    constexpr visitor::is_element<Triangle>     is_triangle;
    constexpr visitor::is_element<Tetrahedron>  is_tetrahedron;
} // namespace element

    using Element = std::variant<
        element::Triangle,
        element::Tetrahedron
        >;
    using Elements = std::vector<Element>;

} // namespace domain
    template <typename Precision>
    struct Domain {
        domain::Nodes<Precision>    nodes;
        domain::Elements            elements;

        std::vector<std::optional<domain::Centroid<Precision>>>
        centroids() const {
            using domain::Element;
            using domain::element::Triangle;
            using domain::element::Tetrahedron;
            using domain::element::is_triangle;
            using domain::element::is_tetrahedron;

            using Centroid  = domain::Centroid<Precision>;

            std::vector<std::optional<Centroid>> cs;
            cs.reserve(elements.size());
            for (const Element& element : elements) {
                if (std::visit(is_triangle, element)) {
                    cs.push_back(std::get<Triangle>(element).centroid(nodes));
                } else if (std::visit(is_tetrahedron, element)) {
                    cs.push_back(std::get<Tetrahedron>(element).centroid(nodes));
                }
            }
            return cs;
        }
    };
} // namespace paulista

#endif // PAULISTA_DOMAIN_HPP__
