#ifndef PAULISTA_SIMPLEX_HPP__
#define PAULISTA_SIMPLEX_HPP__

#include "paulista-point.hpp"

namespace paulista {
namespace simplex {
    struct Point {
        tridimensional::Point u;
    };

    struct Line {
        tridimensional::Point u;
        tridimensional::Point v;
    };

    struct Triangle {
        tridimensional::Point u;
        tridimensional::Point v;
        tridimensional::Point w;
    };

    struct Tetrahedron {
        tridimensional::Point u;
        tridimensional::Point v;
        tridimensional::Point w;
        tridimensional::Point z;
    };

    struct is_point {
        bool operator()(const Point&) const         { return true; }
        bool operator()(const Line&) const          { return false; }
        bool operator()(const Triangle&) const      { return false; }
        bool operator()(const Tetrahedron&) const   { return false; }
    };

    struct is_line {
        bool operator()(const Point&) const         { return false; }
        bool operator()(const Line&) const          { return true; }
        bool operator()(const Triangle&) const      { return false; }
        bool operator()(const Tetrahedron&) const   { return false; }
    };

    struct is_triangle {
        bool operator()(const Point&) const         { return false; }
        bool operator()(const Line&) const          { return false; }
        bool operator()(const Triangle&) const      { return true; }
        bool operator()(const Tetrahedron&) const   { return false; }
    };

    struct is_tetrahedron {
        bool operator()(const Point&) const         { return false; }
        bool operator()(const Line&) const          { return false; }
        bool operator()(const Triangle&) const      { return false; }
        bool operator()(const Tetrahedron&) const   { return true; }
    };
} // namespace simplex
    using Simplex = std::variant<
          simplex::Point
        , simplex::Line
        , simplex::Triangle
        , simplex::Tetrahedron
        >;
} // namespace paulista

#endif // PAULISTA_SIMPLEX_HPP__
