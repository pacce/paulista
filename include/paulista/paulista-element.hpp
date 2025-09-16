#ifndef PAULISTA_ELEMENT_HPP__
#define PAULISTA_ELEMENT_HPP__

#include <variant>
#include <type_traits>
#include "paulista-geometry.hpp"

namespace paulista {
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
        std::optional<paulista::geometry::tridimensional::Point<T>>
        centroid(const std::vector<paulista::geometry::tridimensional::Point<T>>& ns) const {
            if (u >= ns.size()) { return std::nullopt; }
            if (v >= ns.size()) { return std::nullopt; }
            if (w >= ns.size()) { return std::nullopt; }

            std::vector<paulista::geometry::tridimensional::Point<T>> ps = {ns[u], ns[v], ns[w]};
            return paulista::geometry::tridimensional::point::centroid(ps);
        }

        template <typename T>
        std::optional<T>
        area(const std::vector<paulista::geometry::tridimensional::Point<T>>& ns) const {
            if (u >= ns.size()) { return std::nullopt; }
            if (v >= ns.size()) { return std::nullopt; }
            if (w >= ns.size()) { return std::nullopt; }

            const paulista::geometry::tridimensional::Point<T>& p0      = ns[u];
            const paulista::geometry::tridimensional::Point<T>& p1      = ns[v];
            const paulista::geometry::tridimensional::Point<T>& p2      = ns[w];
            const paulista::geometry::tridimensional::Point<T> normal   = (p1 - p0).cross(p2 - p0);
            return normal.norm() / 2;
        }

        template <typename T>
        std::optional<std::vector<geometry::tridimensional::Point<T>>>
        edges(const std::vector<paulista::geometry::tridimensional::Point<T>>& ns) const {
            using P3 = geometry::tridimensional::Point<T>;

            if (u >= ns.size()) { return std::nullopt; }
            if (v >= ns.size()) { return std::nullopt; }
            if (w >= ns.size()) { return std::nullopt; }

            return std::vector<P3>{
                  ns[v] - ns[u]
                , ns[w] - ns[u]
                , ns[w] - ns[v]
            };
        }

        template <typename T>
        std::optional<std::vector<geometry::bidimensional::Point<T>>>
        gradients(const std::vector<paulista::geometry::tridimensional::Point<T>>& ns) const {
            using P2 = geometry::bidimensional::Point<T>;
            using P3 = geometry::tridimensional::Point<T>;

            if (u >= ns.size()) { return std::nullopt; }
            if (v >= ns.size()) { return std::nullopt; }
            if (w >= ns.size()) { return std::nullopt; }

            std::optional<std::vector<P3>> ii   = this->edges(ns);
            if (not ii) { return std::nullopt; }
            std::vector<P2> result = {};
            for (typename std::vector<P3>::const_reverse_iterator it = ii->rbegin(); it != ii->rend(); it++) {
                result.emplace_back(it->y(), it->x());
            }
            return result;
        }
    };

    struct Tetrahedron {
        std::size_t u;
        std::size_t v;
        std::size_t w;
        std::size_t z;

        template <typename T>
        std::optional<paulista::geometry::tridimensional::Point<T>>
        centroid(const std::vector<paulista::geometry::tridimensional::Point<T>>& ns) const {
            if (u >= ns.size()) { return std::nullopt; }
            if (v >= ns.size()) { return std::nullopt; }
            if (w >= ns.size()) { return std::nullopt; }
            if (z >= ns.size()) { return std::nullopt; }

            std::vector<paulista::geometry::tridimensional::Point<T>> ps = {ns[u], ns[v], ns[w], ns[z]};
            return paulista::geometry::tridimensional::point::centroid(ps);
        }

        template <typename T>
        std::optional<T>
        volume(const std::vector<paulista::geometry::tridimensional::Point<T>>& ns) const {
            if (u >= ns.size()) { return std::nullopt; }
            if (v >= ns.size()) { return std::nullopt; }
            if (w >= ns.size()) { return std::nullopt; }
            if (z >= ns.size()) { return std::nullopt; }

            const paulista::geometry::tridimensional::Point<T>& p0 = ns[u];
            const paulista::geometry::tridimensional::Point<T>& p1 = ns[v];
            const paulista::geometry::tridimensional::Point<T>& p2 = ns[w];
            const paulista::geometry::tridimensional::Point<T>& p3 = ns[z];

            const paulista::geometry::tridimensional::Point<T> v1 = p1 - p0;
            const paulista::geometry::tridimensional::Point<T> v2 = p2 - p0;
            const paulista::geometry::tridimensional::Point<T> v3 = p3 - p0;

            const T product = v1.dot(v2.cross(v3)) / 6;
            return paulista::geometry::dimension::abs(product);
        }

        template <typename T>
        std::optional<std::vector<geometry::tridimensional::Point<T>>>
        gradients(const std::vector<paulista::geometry::tridimensional::Point<T>>& ns) const {
            using P3 = geometry::tridimensional::Point<T>;

            if (u >= ns.size()) { return std::nullopt; }
            if (v >= ns.size()) { return std::nullopt; }
            if (w >= ns.size()) { return std::nullopt; }
            if (z >= ns.size()) { return std::nullopt; }

            const P3& p0 = ns[u];
            const P3& p1 = ns[v];
            const P3& p2 = ns[w];
            const P3& p3 = ns[z];

            const P3 v1 = p1 - p0;
            const P3 v2 = p2 - p0;
            const P3 v3 = p3 - p0;

            const T det = v1.dot(v2.cross(v3));
            if (det == T(0)) { return std::nullopt; }

            const P3 n1 = v2.cross(v3) / static_cast<std::int64_t>(det);
            const P3 n2 = v3.cross(v1) / static_cast<std::int64_t>(det);
            const P3 n3 = v1.cross(v2) / static_cast<std::int64_t>(det);
            const P3 n0 = -(n1 + n2 + n3);

            return std::vector<P3>{n0, n1, n2, n3};
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
} // namespace paulista

#endif // PAULISTA_ELEMENT_HPP__
