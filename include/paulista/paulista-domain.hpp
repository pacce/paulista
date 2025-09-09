#ifndef PAULISTA_DOMAIN_HPP__
#define PAULISTA_DOMAIN_HPP__

#include <variant>
#include <type_traits>
#include "paulista-geometry.hpp"

namespace paulista {
namespace domain {
namespace element {
namespace visitor {
    template <typename T>
    struct is_element {
        template <typename U>
        bool operator()(const U& shape) const {
            return std::is_same_v<T, U>;
        }
    };
} // namespace visitor
    struct Triangle {
        std::size_t u;
        std::size_t v;
        std::size_t w;
    };

    struct Tetrahedron {
        std::size_t u;
        std::size_t v;
        std::size_t w;
        std::size_t z;
    };

    constexpr visitor::is_element<Triangle>     is_triangle;
    constexpr visitor::is_element<Tetrahedron>  is_tetrahedron;
} // namespace element
    template <typename Precision>
    using Nodes = std::vector<paulista::geometry::tridimensional::Point<Precision>>;

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
