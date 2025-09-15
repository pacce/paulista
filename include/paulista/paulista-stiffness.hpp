#ifndef PAULISTA_STIFFNESS_HPP__
#define PAULISTA_STIFFNESS_HPP__

#include "paulista-domain.hpp"
#include <iostream>
#include <vector>
#include <optional>

namespace paulista {
namespace stiffness {
    template<typename Precision>
    struct Triplet {
        static_assert(std::is_floating_point_v<Precision>, "Precision must be a floating point type");

        std::size_t row;
        std::size_t col;
        Precision value;
    };

    template<typename Precision>
    using Triplets = std::vector<Triplet<Precision>>;

namespace triangle {
    template<typename Dimension, typename U>
    std::optional<Triplets<U>>
    local(
              const domain::element::Triangle&  triangle
            , const domain::Nodes<Dimension>&   nodes
            , U                                 conductivity = U()
            ) 
    {
        static_assert(std::is_floating_point_v<U>, "U must be a floating point type");

        using P2 = geometry::bidimensional::Point<Dimension>;
        using P3 = geometry::tridimensional::Point<Dimension>;

        if (triangle.u >= nodes.size()) { return std::nullopt; }
        if (triangle.v >= nodes.size()) { return std::nullopt; }
        if (triangle.w >= nodes.size()) { return std::nullopt; }

        std::vector<std::size_t> indices = {
              triangle.u
            , triangle.v
            , triangle.w
        };

        std::optional<Dimension> area = triangle.area(nodes);
        if (not area)               { return std::nullopt; }
        if (*area == Dimension(0))  { return std::nullopt; }

        std::optional<std::vector<P2>> gradients = triangle.gradients(nodes);
        if (not gradients) { return std::nullopt; }

        U denominator = 2 * static_cast<U>(*area) * geometry::dimension::conversion::inverse<Dimension>::value;

        Triplets<U> triplets;
        triplets.reserve(9);
        for (std::size_t i = 0; i < 3; i++) {
        for (std::size_t j = 0; j < 3; j++) {
            triplets.emplace_back(
                      indices[i]
                    , indices[j]
                    , (conductivity * static_cast<U>(gradients->at(i).dot(gradients->at(j)))) / (denominator * denominator)
            );
        }
        }

        return triplets;
    }
} // namespace triangle
} // namespace stiffness
} // namespace paulista

#endif // PAULISTA_STIFFNESS_HPP__
