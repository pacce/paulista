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

    Decimeter::Decimeter() : value_(0) {}
    Decimeter::Decimeter(std::int32_t value) : value_(value) {}

    Decimeter::Decimeter(const Meter&      value) : value_(static_cast<std::int32_t>(value) * 1e1){}
    Decimeter::Decimeter(const Centimeter& value) : value_(static_cast<std::int32_t>(value) / 1e1){}
    Decimeter::Decimeter(const Millimeter& value) : value_(static_cast<std::int32_t>(value) / 1e2){}
    Decimeter::Decimeter(const Micrometer& value) : value_(static_cast<std::int32_t>(value) / 1e5){}

    std::strong_ordering
    operator<=>(const Decimeter& lhs, const Decimeter& rhs) {
        return lhs.value_ <=> rhs.value_;
    }

    Decimeter&
    Decimeter::operator+=(const Decimeter& rhs) {
        value_ += rhs.value_; return *this;
    }

    Decimeter&
    Decimeter::operator-=(const Decimeter& rhs) {
        value_ -= rhs.value_; return *this;
    }

    Decimeter&
    Decimeter::operator*=(int32_t value) {
        value_ *= value;
        return *this;
    }

    Decimeter&
    Decimeter::operator/=(int32_t value) {
        value_ /= value;
        return *this;
    }

    Decimeter
    operator+(Decimeter lhs, const Decimeter& rhs) {
        lhs += rhs; return lhs;
    }

    Decimeter
    operator-(Decimeter lhs, const Decimeter& rhs) {
        lhs -= rhs; return lhs;
    }

    Decimeter
    operator-(const Decimeter& lhs) {
        Decimeter result;
        result.value_ -= lhs.value_;

        return result;
    }

    Decimeter
    operator*(std::int32_t value, Decimeter p) {
        p *= value; return p;
    }

    Decimeter
    operator*(Decimeter p, std::int32_t value) {
        p *= value; return p;
    }

    Decimeter
    operator/(Decimeter p, std::int32_t value) {
        p /= value; return p;
    }

    std::ostream&
    operator<<(std::ostream& os, const Decimeter& p) {
        return os << static_cast<std::int32_t>(p.value_) << "dm";
    }

    Centimeter::Centimeter() : value_(0) {}
    Centimeter::Centimeter(std::int32_t value) : value_(value) {}

    Centimeter::Centimeter(const Meter&      value) : value_(static_cast<std::int32_t>(value) * 1e2){}
    Centimeter::Centimeter(const Decimeter&  value) : value_(static_cast<std::int32_t>(value) * 1e1){}
    Centimeter::Centimeter(const Millimeter& value) : value_(static_cast<std::int32_t>(value) / 1e1){}
    Centimeter::Centimeter(const Micrometer& value) : value_(static_cast<std::int32_t>(value) / 1e4){}

    std::strong_ordering
    operator<=>(const Centimeter& lhs, const Centimeter& rhs) {
        return lhs.value_ <=> rhs.value_;
    }

    Centimeter&
    Centimeter::operator+=(const Centimeter& rhs) {
        value_ += rhs.value_; return *this;
    }

    Centimeter&
    Centimeter::operator-=(const Centimeter& rhs) {
        value_ -= rhs.value_; return *this;
    }

    Centimeter&
    Centimeter::operator*=(int32_t value) {
        value_ *= value;
        return *this;
    }

    Centimeter&
    Centimeter::operator/=(int32_t value) {
        value_ /= value;
        return *this;
    }

    Centimeter
    operator+(Centimeter lhs, const Centimeter& rhs) {
        lhs += rhs; return lhs;
    }

    Centimeter
    operator-(Centimeter lhs, const Centimeter& rhs) {
        lhs -= rhs; return lhs;
    }

    Centimeter
    operator-(const Centimeter& lhs) {
        Centimeter result;
        result.value_ -= lhs.value_;

        return result;
    }

    Centimeter
    operator*(std::int32_t value, Centimeter p) {
        p *= value; return p;
    }

    Centimeter
    operator*(Centimeter p, std::int32_t value) {
        p *= value; return p;
    }

    Centimeter
    operator/(Centimeter p, std::int32_t value) {
        p /= value; return p;
    }

    std::ostream&
    operator<<(std::ostream& os, const Centimeter& p) {
        return os << static_cast<std::int32_t>(p.value_) << "cm";
    }

    Millimeter::Millimeter() : value_(0) {}
    Millimeter::Millimeter(std::int32_t value) : value_(value) {}

    Millimeter::Millimeter(const Meter&      value) : value_(static_cast<std::int32_t>(value) * 1e3){}
    Millimeter::Millimeter(const Decimeter&  value) : value_(static_cast<std::int32_t>(value) * 1e2){}
    Millimeter::Millimeter(const Centimeter& value) : value_(static_cast<std::int32_t>(value) * 1e1){}
    Millimeter::Millimeter(const Micrometer& value) : value_(static_cast<std::int32_t>(value) / 1e3){}

    std::strong_ordering
    operator<=>(const Millimeter& lhs, const Millimeter& rhs) {
        return lhs.value_ <=> rhs.value_;
    }

    Millimeter&
    Millimeter::operator+=(const Millimeter& rhs) {
        value_ += rhs.value_; return *this;
    }

    Millimeter&
    Millimeter::operator-=(const Millimeter& rhs) {
        value_ -= rhs.value_; return *this;
    }

    Millimeter&
    Millimeter::operator*=(int32_t value) {
        value_ *= value;
        return *this;
    }

    Millimeter&
    Millimeter::operator/=(int32_t value) {
        value_ /= value;
        return *this;
    }

    Millimeter
    operator+(Millimeter lhs, const Millimeter& rhs) {
        lhs += rhs; return lhs;
    }

    Millimeter
    operator-(Millimeter lhs, const Millimeter& rhs) {
        lhs -= rhs; return lhs;
    }

    Millimeter
    operator-(const Millimeter& lhs) {
        Millimeter result;
        result.value_ -= lhs.value_;

        return result;
    }

    Millimeter
    operator*(std::int32_t value, Millimeter p) {
        p *= value; return p;
    }

    Millimeter
    operator*(Millimeter p, std::int32_t value) {
        p *= value; return p;
    }

    Millimeter
    operator/(Millimeter p, std::int32_t value) {
        p /= value; return p;
    }

    std::ostream&
    operator<<(std::ostream& os, const Millimeter& p) {
        return os << static_cast<std::int32_t>(p.value_) << "mm";
    }

    Micrometer::Micrometer() : value_(0) {}
    Micrometer::Micrometer(std::int32_t value) : value_(value) {}

    Micrometer::Micrometer(const Meter&      value) : value_(static_cast<std::int32_t>(value) * 1e6){}
    Micrometer::Micrometer(const Decimeter&  value) : value_(static_cast<std::int32_t>(value) * 1e5){}
    Micrometer::Micrometer(const Centimeter& value) : value_(static_cast<std::int32_t>(value) * 1e4){}
    Micrometer::Micrometer(const Millimeter& value) : value_(static_cast<std::int32_t>(value) * 1e3){}

    std::strong_ordering
    operator<=>(const Micrometer& lhs, const Micrometer& rhs) {
        return lhs.value_ <=> rhs.value_;
    }

    Micrometer&
    Micrometer::operator+=(const Micrometer& rhs) {
        value_ += rhs.value_; return *this;
    }

    Micrometer&
    Micrometer::operator-=(const Micrometer& rhs) {
        value_ -= rhs.value_; return *this;
    }

    Micrometer&
    Micrometer::operator*=(int32_t value) {
        value_ *= value;
        return *this;
    }

    Micrometer&
    Micrometer::operator/=(int32_t value) {
        value_ /= value;
        return *this;
    }

    Micrometer
    operator+(Micrometer lhs, const Micrometer& rhs) {
        lhs += rhs; return lhs;
    }

    Micrometer
    operator-(Micrometer lhs, const Micrometer& rhs) {
        lhs -= rhs; return lhs;
    }

    Micrometer
    operator-(const Micrometer& lhs) {
        Micrometer result;
        result.value_ -= lhs.value_;

        return result;
    }

    Micrometer
    operator*(std::int32_t value, Micrometer p) {
        p *= value; return p;
    }

    Micrometer
    operator*(Micrometer p, std::int32_t value) {
        p *= value; return p;
    }

    Micrometer
    operator/(Micrometer p, std::int32_t value) {
        p /= value; return p;
    }

    std::ostream&
    operator<<(std::ostream& os, const Micrometer& p) {
        return os << static_cast<std::int32_t>(p.value_) << "um";
    }

    Meter::operator Decimeter() const    { return Decimeter(*this); }
    Meter::operator Centimeter() const   { return Centimeter(*this); }
    Meter::operator Millimeter() const   { return Millimeter(*this); }
    Meter::operator Micrometer() const   { return Micrometer(*this); }

    Decimeter::operator Meter() const        { return Meter(*this); }
    Decimeter::operator Centimeter() const   { return Centimeter(*this); }
    Decimeter::operator Millimeter() const   { return Millimeter(*this); }
    Decimeter::operator Micrometer() const   { return Micrometer(*this); }

    Centimeter::operator Meter() const       { return Meter(*this); }
    Centimeter::operator Decimeter() const   { return Decimeter(*this); }
    Centimeter::operator Millimeter() const  { return Millimeter(*this); }
    Centimeter::operator Micrometer() const  { return Micrometer(*this); }

    Millimeter::operator Meter() const       { return Meter(*this); }
    Millimeter::operator Decimeter() const   { return Decimeter(*this); }
    Millimeter::operator Centimeter() const  { return Centimeter(*this); }
    Millimeter::operator Micrometer() const  { return Micrometer(*this); }

    Micrometer::operator Meter() const       { return Meter(*this); }
    Micrometer::operator Decimeter() const   { return Decimeter(*this); }
    Micrometer::operator Centimeter() const  { return Centimeter(*this); }
    Micrometer::operator Millimeter() const  { return Millimeter(*this); }

} // namespace dimension
} // namespace geometry
} // namespace paulista
