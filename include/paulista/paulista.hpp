#ifndef PAULISTA_HPP__
#define PAULISTA_HPP__

#include <cstdint>
#include <ostream>

namespace paulista {
namespace dimension {
    using Millimeter = std::int32_t;
    using Micrometer = std::int32_t;
} // namespace dimension
namespace tridimensional {
    class Point {
        public:
            Point() : x_(0), y_(0), z_(0) {}
            Point(dimension::Millimeter x, dimension::Millimeter y, dimension::Millimeter z)
                : x_(x * 1000)
                , y_(y * 1000)
                , z_(z * 1000)
            {}

            friend bool
            operator==(const Point& lhs, const Point& rhs) {
                return  (lhs.x_ / 1000) == (rhs.x_ / 1000)
                    and (lhs.y_ / 1000) == (rhs.y_ / 1000)
                    and (lhs.z_ / 1000) == (rhs.z_ / 1000)
                    ;
            }

            friend bool
            operator!=(const Point& lhs, const Point& rhs) {
                return not (lhs == rhs);
            }

            Point&
            operator+=(const Point& other) {
                x_ += other.x_;
                y_ += other.y_;
                z_ += other.z_;
                return *this;
            }

            Point&
            operator-=(const Point& other) {
                x_ -= other.x_;
                y_ -= other.y_;
                z_ -= other.z_;
                return *this;
            }

            friend Point
            operator+(Point lhs, const Point& rhs) {
                lhs += rhs; return lhs;
            }

            friend Point
            operator-(const Point& rhs) {
                Point p;
                p.x_ = -rhs.x_;
                p.y_ = -rhs.y_;
                p.z_ = -rhs.z_;

                return p;
            }

            friend Point
            operator-(Point lhs, const Point& rhs) {
                lhs -= rhs; return lhs;
            }

            friend std::ostream&
            operator<<(std::ostream& os, const Point& p) {
                return os   << "(" << (p.x_ / 1000)
                            << "," << (p.y_ / 1000)
                            << "," << (p.z_ / 1000)
                            << ")"
                            ;
            }
        private:
            dimension::Micrometer x_;
            dimension::Micrometer y_;
            dimension::Micrometer z_;
    };
} // namespace tridimensional {
} // namespace paulista

#endif // PAULISTA_HPP__
