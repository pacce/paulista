#ifndef PAULISTA_GEOMETRY_POINT_HPP__
#define PAULISTA_GEOMETRY_POINT_HPP__

#include <cstdint>
#include <optional>
#include <ostream>
#include <vector>

#include "paulista-dimension.hpp"

namespace paulista {
namespace geometry {
namespace bidimensional {
    template <typename T>
    class Point {
        static_assert(dimension::is_dimension<T>::value);
        public:
            Point() : x_(0), y_(0) {}
            Point(T x, T y) : x_(x), y_(y) {}

            friend bool
            operator==(const Point<T>& lhs, const Point<T>& rhs) {
                return  (lhs.x_ == rhs.x_)
                    and (lhs.y_ == rhs.y_)
                    ;
            }

            friend bool
            operator!=(const Point<T>& lhs, const Point<T>& rhs) {
                return not (lhs == rhs);
            }

            friend std::ostream&
            operator<<(std::ostream& os, const Point<T>& p) {
                return os << "(" << p.x_ << "," << p.y_ << ")";
            }

            Point<T>&
            operator+=(const Point<T>& other) {
                x_ += other.x_;
                y_ += other.y_;
                return *this;
            }

            friend Point<T>
            operator+(Point<T> lhs, const Point<T>& rhs) {
                lhs += rhs; return lhs;
            }

            Point<T>&
            operator-=(const Point<T>& other) {
                x_ -= other.x_;
                y_ -= other.y_;
                return *this;
            }

            friend Point<T>
            operator-(Point<T> lhs, const Point<T>& rhs) {
                lhs -= rhs; return lhs;
            }

            friend Point<T>
            operator-(const Point<T>& rhs) {
                Point<T> p;
                p.x_ = -rhs.x_;
                p.y_ = -rhs.y_;

                return p;
            }

            Point<T>&
            operator*=(int32_t value) {
                x_ *= value;
                y_ *= value;
                return *this;
            }

            friend Point<T>
            operator*(std::int32_t value, Point<T> p) {
                p *= value; return p;
            }

            friend Point<T>
            operator*(Point<T> p, std::int32_t value) {
                p *= value; return p;
            }

            Point<T>&
            operator/=(int32_t value) {
                x_ /= value;
                y_ /= value;
                return *this;
            }

            friend Point<T>
            operator/(Point<T> p, std::int32_t value) {
                p /= value; return p;
            }

            T
            cross(const Point<T>& lhs) const {
                return  (x_ * static_cast<std::int32_t>(lhs.y_))
                      - (y_ * static_cast<std::int32_t>(lhs.x_));
            }

            T
            dot(const Point<T>& lhs) const {
                return  (x_ * static_cast<std::int32_t>(lhs.x_))
                    +   (y_ * static_cast<std::int32_t>(lhs.y_))
                    ;
            }

            T
            norm() const {
                return paulista::geometry::dimension::sqrt(this->dot(*this));
            }

            T x() const { return x_; }
            T y() const { return y_; }

            template <typename U>
            explicit operator Point<U>() const {
                static_assert(dimension::is_dimension<U>::value);

                return Point<U>(
                          static_cast<U>(x_)
                        , static_cast<U>(y_)
                        );
            };
        private:
            T x_;
            T y_;
    };
namespace point {
    template <typename T>
    inline std::optional<Point<T>>
    centroid(const std::vector<Point<T>>& ps) {
        static_assert(dimension::is_dimension<T>::value);

        if (ps.empty()) {
            return std::nullopt;
        } else if (ps.size() == 1) {
            return ps.front();
        } else {
            std::int32_t denominator = ps.size();

            Point<T> p = ps.front();
            for (std::int32_t i = 1; i < denominator; i++) { p += ps[i]; }
            return (p / denominator);
        }
    };
} // namespace point
} // namespace bidimensional
namespace tridimensional {
    template <typename T>
    class Point {
        static_assert(dimension::is_dimension<T>::value);
        public:
            Point() : x_(0), y_(0), z_(0) {}
            Point(T x, T y, T z) : x_(x), y_(y), z_(z) {}

            friend bool
            operator==(const Point<T>& lhs, const Point<T>& rhs) {
                return  (lhs.x_ == rhs.x_)
                    and (lhs.y_ == rhs.y_)
                    and (lhs.z_ == rhs.z_)
                    ;
            }

            friend bool
            operator!=(const Point<T>& lhs, const Point<T>& rhs) {
                return not (lhs == rhs);
            }

            friend std::ostream&
            operator<<(std::ostream& os, const Point<T>& p) {
                return os << "(" << p.x_ << "," << p.y_ << "," << p.z_ << ")";
            }

            Point<T>&
            operator+=(const Point<T>& other) {
                x_ += other.x_;
                y_ += other.y_;
                z_ += other.z_;
                return *this;
            }

            friend Point<T>
            operator+(Point<T> lhs, const Point<T>& rhs) {
                lhs += rhs; return lhs;
            }

            Point<T>&
            operator-=(const Point<T>& other) {
                x_ -= other.x_;
                y_ -= other.y_;
                z_ -= other.z_;
                return *this;
            }

            friend Point<T>
            operator-(Point<T> lhs, const Point<T>& rhs) {
                lhs -= rhs; return lhs;
            }

            friend Point<T>
            operator-(const Point<T>& rhs) {
                Point<T> p;
                p.x_ = -rhs.x_;
                p.y_ = -rhs.y_;
                p.z_ = -rhs.z_;

                return p;
            }

            Point<T>&
            operator*=(int32_t value) {
                x_ *= value;
                y_ *= value;
                z_ *= value;
                return *this;
            }

            friend Point<T>
            operator*(std::int32_t value, Point<T> p) {
                p *= value; return p;
            }

            friend Point<T>
            operator*(Point<T> p, std::int32_t value) {
                p *= value; return p;
            }

            Point<T>&
            operator/=(int32_t value) {
                x_ /= value;
                y_ /= value;
                z_ /= value;
                return *this;
            }

            friend Point<T>
            operator/(Point<T> p, std::int32_t value) {
                p /= value; return p;
            }

            T
            dot(const Point<T>& lhs) const {
                return  (x_ * static_cast<std::int32_t>(lhs.x_))
                    +   (y_ * static_cast<std::int32_t>(lhs.y_))
                    +   (z_ * static_cast<std::int32_t>(lhs.z_))
                    ;
            }

            T
            norm() const {
                return paulista::geometry::dimension::sqrt(this->dot(*this));
            }

            Point<T>
            cross(const Point<T>& lhs) const {
                T x = (y_ * static_cast<std::int32_t>(lhs.z_))
                    - (z_ * static_cast<std::int32_t>(lhs.y_));

                T y = (z_ * static_cast<std::int32_t>(lhs.x_))
                    - (x_ * static_cast<std::int32_t>(lhs.z_));

                T z = (x_ * static_cast<std::int32_t>(lhs.y_))
                    - (y_ * static_cast<std::int32_t>(lhs.x_));
                return Point<T>(x, y, z);
            }

            T x() const { return x_; }
            T y() const { return y_; }
            T z() const { return z_; }

            template <typename U>
            explicit operator Point<U>() const { 
                static_assert(dimension::is_dimension<U>::value);

                return Point<U>(
                          static_cast<U>(x_)
                        , static_cast<U>(y_)
                        , static_cast<U>(z_)
                        );
            };
        private:
            T x_;
            T y_;
            T z_;
    };
namespace point {
    template <typename T>
    inline std::optional<Point<T>>
    centroid(const std::vector<Point<T>>& ps) {
        static_assert(dimension::is_dimension<T>::value);

        if (ps.empty()) {
            return std::nullopt;
        } else if (ps.size() == 1) {
            return ps.front();
        } else {
            std::int32_t denominator = ps.size();

            Point<T> p = ps.front();
            for (std::int32_t i = 1; i < denominator; i++) { p += ps[i]; }
            return (p / denominator);
        }
    };
} // namespace point
} // namespace tridimensional
} // namespace geometry
} // namespace paulista

#endif // PAULISTA_GEOMETRY_POINT_HPP__
