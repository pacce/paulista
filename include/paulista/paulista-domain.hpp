#ifndef PAULISTA_DOMAIN_HPP__
#define PAULISTA_DOMAIN_HPP__

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
    };
} // namespace paulista

#endif // PAULISTA_DOMAIN_HPP__
