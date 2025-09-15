#ifndef PAULISTA_DOMAIN_HPP__
#define PAULISTA_DOMAIN_HPP__

#include <cmath>
#include <variant>
#include <type_traits>

#include "paulista-element.hpp"
#include "paulista-geometry.hpp"

namespace paulista {
namespace domain {
    template <typename Precision> using Node        = paulista::geometry::tridimensional::Point<Precision>;
    template <typename Precision> using Nodes       = std::vector<Node<Precision>>;

    template <typename Precision> using Centroid    = paulista::geometry::tridimensional::Point<Precision>;
    template <typename Precision> using Centroids   = std::vector<Node<Precision>>;
} // namespace domain
    template <typename Precision>
    struct Domain {
        domain::Nodes<Precision>    nodes;
        Elements                    elements;

        std::vector<std::optional<domain::Centroid<Precision>>>
        centroids() const {
            using element::Triangle;
            using element::Tetrahedron;
            using element::is_triangle;
            using element::is_tetrahedron;

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
