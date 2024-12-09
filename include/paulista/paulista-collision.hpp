#ifndef PAULISTA_COLLISION_HPP__
#define PAULISTA_COLLISION_HPP__

#include <optional>

#include "paulista-point.hpp"
#include "paulista-simplex.hpp"

namespace paulista {
namespace collision {
    using Shape = std::vector<tridimensional::Point>;

    inline std::optional<tridimensional::Point>
    support(const Shape& ps, const tridimensional::Vector& v) {
        if (ps.empty()) {
            return std::nullopt;
        } else {
            tridimensional::Point choice = ps.front();
            for (const tridimensional::Point& p : ps) {
                if (p.dot(v) > choice.dot(v)) { choice = p; }
            }
            return choice;
        }
    }

    inline std::optional<bool>
    detect(const Shape& xs, const Shape& ys) {
        if (xs.empty() or ys.empty()) {
            return std::nullopt;
        } else {
            return std::nullopt;
        }
    }
} // namespace collision
} // namespace paulista

#endif // PAULISTA_COLLISION_HPP__
