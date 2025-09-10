#include "paulista/geometry/paulista-dimension.hpp"

namespace paulista {
namespace geometry {
namespace dimension {
    Meter::Meter() : value_(0) {}
    Meter::Meter(std::int32_t value) : value_(value) {}

    Meter::Meter(const Decimeter&  value) : value_(static_cast<std::int32_t>(value) / 1e1){}
    Meter::Meter(const Centimeter& value) : value_(static_cast<std::int32_t>(value) / 1e2){}
    Meter::Meter(const Millimeter& value) : value_(static_cast<std::int32_t>(value) / 1e3){}
    Meter::Meter(const Micrometer& value) : value_(static_cast<std::int32_t>(value) / 1e6){}

    std::strong_ordering
    operator<=>(const Meter& lhs, const Meter& rhs) {
        return lhs.value_ <=> rhs.value_;
    }

    Meter&
    Meter::operator+=(const Meter& rhs) {
        value_ += rhs.value_; return *this;
    }

    Meter&
    Meter::operator-=(const Meter& rhs) {
        value_ -= rhs.value_; return *this;
    }

    Meter&
    Meter::operator*=(int32_t value) {
        value_ *= value;
        return *this;
    }

    Meter&
    Meter::operator/=(int32_t value) {
        value_ /= value;
        return *this;
    }

    Meter
    operator+(Meter lhs, const Meter& rhs) {
        lhs += rhs; return lhs;
    }

    Meter
    operator-(Meter lhs, const Meter& rhs) {
        lhs -= rhs; return lhs;
    }

    Meter
    operator-(const Meter& lhs) {
        Meter result;
        result.value_ -= lhs.value_;

        return result;
    }

    Meter
    operator*(std::int32_t value, Meter p) {
        p *= value; return p;
    }

    Meter
    operator*(Meter p, std::int32_t value) {
        p *= value; return p;
    }

    Meter
    operator/(Meter p, std::int32_t value) {
        p /= value; return p;
    }

    std::ostream&
    operator<<(std::ostream& os, const Meter& p) {
        return os << static_cast<std::int32_t>(p.value_) << "m";
    }

} // namespace dimension
} // namespace geometry
} // namespace paulista
