#ifndef PAULISTA_GEOMETRY_DIMENSION_HPP__
#define PAULISTA_GEOMETRY_DIMENSION_HPP__

#include <cstdint>
#include <ostream>

namespace paulista {
namespace geometry {
namespace dimension {
    class Meter;
    class Decimeter;
    class Centimeter;
    class Millimeter;
    class Micrometer;

    template <typename T> 
    struct is_dimension : public std::false_type {};

    template<> struct is_dimension<Meter> : public std::true_type {};
    template<> struct is_dimension<Decimeter> : public std::true_type {};
    template<> struct is_dimension<Centimeter> : public std::true_type {};
    template<> struct is_dimension<Millimeter> : public std::true_type {};
    template<> struct is_dimension<Micrometer> : public std::true_type {};
    template<> struct is_dimension<Meter&> : public std::true_type {};
    template<> struct is_dimension<Decimeter&> : public std::true_type {};
    template<> struct is_dimension<Centimeter&> : public std::true_type {};
    template<> struct is_dimension<Millimeter&> : public std::true_type {};
    template<> struct is_dimension<Micrometer&> : public std::true_type {};
    template<> struct is_dimension<const Meter> : public std::true_type {};
    template<> struct is_dimension<const Decimeter> : public std::true_type {};
    template<> struct is_dimension<const Centimeter> : public std::true_type {};
    template<> struct is_dimension<const Millimeter> : public std::true_type {};
    template<> struct is_dimension<const Micrometer> : public std::true_type {};
    template<> struct is_dimension<const Meter&> : public std::true_type {};
    template<> struct is_dimension<const Decimeter&> : public std::true_type {};
    template<> struct is_dimension<const Centimeter&> : public std::true_type {};
    template<> struct is_dimension<const Millimeter&> : public std::true_type {};
    template<> struct is_dimension<const Micrometer&> : public std::true_type {};

    class Meter {
        public:
            Meter();
            Meter(std::int32_t value);

            Meter(const Decimeter& value);
            Meter(const Centimeter& value);
            Meter(const Millimeter& value);
            Meter(const Micrometer& value);

            friend std::strong_ordering
            operator<=>(const Meter& lhs, const Meter& rhs);

            friend bool operator==(const Meter& lhs, const Meter& rhs) = default;
            friend bool operator!=(const Meter& lhs, const Meter& rhs) = default;
            friend bool operator<(const Meter& lhs, const Meter& rhs) = default;
            friend bool operator<=(const Meter& lhs, const Meter& rhs) = default;
            friend bool operator>(const Meter& lhs, const Meter& rhs) = default;
            friend bool operator>=(const Meter& lhs, const Meter& rhs) = default;

            Meter& operator+=(const Meter& rhs);
            Meter& operator-=(const Meter& rhs);
            Meter& operator*=(int32_t value);
            Meter& operator/=(int32_t value);

            friend Meter operator+(Meter lhs, const Meter& rhs);
            friend Meter operator-(Meter lhs, const Meter& rhs);
            friend Meter operator-(const Meter& lhs);

            friend Meter operator*(std::int32_t value, Meter p);
            friend Meter operator*(Meter p, std::int32_t value);
            friend Meter operator/(Meter p, std::int32_t value);

            friend std::ostream&
            operator<<(std::ostream& os, const Meter& p);

            explicit operator std::int32_t() const { return value_; }

            explicit operator Decimeter() const;
            explicit operator Centimeter() const;
            explicit operator Millimeter() const;
            explicit operator Micrometer() const;
        private:
            std::int32_t value_;
    };

    class Decimeter {
        public:
            Decimeter() : value_(0) {}
            Decimeter(std::int32_t value) : value_(value) {}

            Decimeter(const Meter& value);
            Decimeter(const Centimeter& value);
            Decimeter(const Millimeter& value);
            Decimeter(const Micrometer& value);

            friend std::strong_ordering
            operator<=>(const Decimeter& lhs, const Decimeter& rhs) {
                return lhs.value_ <=> rhs.value_;
            }

            friend bool operator==(const Decimeter& lhs, const Decimeter& rhs) = default;
            friend bool operator!=(const Decimeter& lhs, const Decimeter& rhs) = default;
            friend bool operator<(const Decimeter& lhs, const Decimeter& rhs) = default;
            friend bool operator<=(const Decimeter& lhs, const Decimeter& rhs) = default;
            friend bool operator>(const Decimeter& lhs, const Decimeter& rhs) = default;
            friend bool operator>=(const Decimeter& lhs, const Decimeter& rhs) = default;

            Decimeter&
            operator+=(const Decimeter& rhs) {
                value_ += rhs.value_; return *this;
            }

            Decimeter&
            operator-=(const Decimeter& rhs) {
                value_ -= rhs.value_; return *this;
            }

            Decimeter&
            operator*=(int32_t value) {
                value_ *= value;
                return *this;
            }

            Decimeter&
            operator/=(int32_t value) {
                value_ /= value;
                return *this;
            }

            friend Decimeter
            operator+(Decimeter lhs, const Decimeter& rhs) {
                lhs += rhs; return lhs;
            }

            friend Decimeter
            operator-(Decimeter lhs, const Decimeter& rhs) {
                lhs -= rhs; return lhs;
            }

            friend Decimeter
            operator-(const Decimeter& lhs) {
                Decimeter result;
                result.value_ -= lhs.value_;

                return result;
            }

            friend Decimeter
            operator*(std::int32_t value, Decimeter p) {
                p *= value; return p;
            }

            friend Decimeter
            operator*(Decimeter p, std::int32_t value) {
                p *= value; return p;
            }

            friend Decimeter
            operator/(Decimeter p, std::int32_t value) {
                p /= value; return p;
            }

            friend std::ostream&
            operator<<(std::ostream& os, const Decimeter& p) {
                return os << static_cast<std::int32_t>(p.value_) << "dm";
            }

            explicit operator std::int32_t() const { return value_; }

            explicit operator Meter() const;
            explicit operator Centimeter() const;
            explicit operator Millimeter() const;
            explicit operator Micrometer() const;
        private:
            std::int32_t value_;
    };

    class Centimeter {
        public:
            Centimeter() : value_(0) {}
            Centimeter(std::int32_t value) : value_(value) {}

            Centimeter(const Meter& value);
            Centimeter(const Decimeter& value);
            Centimeter(const Millimeter& value);
            Centimeter(const Micrometer& value);

            friend std::strong_ordering
            operator<=>(const Centimeter& lhs, const Centimeter& rhs) {
                return lhs.value_ <=> rhs.value_;
            }

            friend bool operator==(const Centimeter& lhs, const Centimeter& rhs) = default;
            friend bool operator!=(const Centimeter& lhs, const Centimeter& rhs) = default;
            friend bool operator<(const Centimeter& lhs, const Centimeter& rhs) = default;
            friend bool operator<=(const Centimeter& lhs, const Centimeter& rhs) = default;
            friend bool operator>(const Centimeter& lhs, const Centimeter& rhs) = default;
            friend bool operator>=(const Centimeter& lhs, const Centimeter& rhs) = default;

            Centimeter&
            operator+=(const Centimeter& rhs) {
                value_ += rhs.value_; return *this;
            }

            Centimeter&
            operator-=(const Centimeter& rhs) {
                value_ -= rhs.value_; return *this;
            }

            Centimeter&
            operator*=(int32_t value) {
                value_ *= value;
                return *this;
            }

            Centimeter&
            operator/=(int32_t value) {
                value_ /= value;
                return *this;
            }

            friend Centimeter
            operator+(Centimeter lhs, const Centimeter& rhs) {
                lhs += rhs; return lhs;
            }

            friend Centimeter
            operator-(Centimeter lhs, const Centimeter& rhs) {
                lhs -= rhs; return lhs;
            }

            friend Centimeter
            operator-(const Centimeter& lhs) {
                Centimeter result;
                result.value_ -= lhs.value_;

                return result;
            }

            friend Centimeter
            operator*(std::int32_t value, Centimeter p) {
                p *= value; return p;
            }

            friend Centimeter
            operator*(Centimeter p, std::int32_t value) {
                p *= value; return p;
            }

            friend Centimeter
            operator/(Centimeter p, std::int32_t value) {
                p /= value; return p;
            }

            friend std::ostream&
            operator<<(std::ostream& os, const Centimeter& p) {
                return os << static_cast<std::int32_t>(p.value_) << "cm";
            }

            explicit operator std::int32_t() const { return value_; }

            explicit operator Meter() const;
            explicit operator Decimeter() const;
            explicit operator Millimeter() const;
            explicit operator Micrometer() const;
        private:
            std::int32_t value_;
    };

    class Millimeter {
        public:
            Millimeter() : value_(0) {}
            Millimeter(std::int32_t value) : value_(value) {}

            Millimeter(const Meter& value);
            Millimeter(const Decimeter& value);
            Millimeter(const Centimeter& value);
            Millimeter(const Micrometer& value);

            friend std::strong_ordering
            operator<=>(const Millimeter& lhs, const Millimeter& rhs) {
                return lhs.value_ <=> rhs.value_;
            }

            friend bool operator==(const Millimeter& lhs, const Millimeter& rhs) = default;
            friend bool operator!=(const Millimeter& lhs, const Millimeter& rhs) = default;
            friend bool operator<(const Millimeter& lhs, const Millimeter& rhs) = default;
            friend bool operator<=(const Millimeter& lhs, const Millimeter& rhs) = default;
            friend bool operator>(const Millimeter& lhs, const Millimeter& rhs) = default;
            friend bool operator>=(const Millimeter& lhs, const Millimeter& rhs) = default;

            Millimeter&
            operator+=(const Millimeter& rhs) {
                value_ += rhs.value_; return *this;
            }

            Millimeter&
            operator-=(const Millimeter& rhs) {
                value_ -= rhs.value_; return *this;
            }

            Millimeter&
            operator*=(int32_t value) {
                value_ *= value;
                return *this;
            }

            Millimeter&
            operator/=(int32_t value) {
                value_ /= value;
                return *this;
            }

            friend Millimeter
            operator+(Millimeter lhs, const Millimeter& rhs) {
                lhs += rhs; return lhs;
            }

            friend Millimeter
            operator-(Millimeter lhs, const Millimeter& rhs) {
                lhs -= rhs; return lhs;
            }

            friend Millimeter
            operator-(const Millimeter& lhs) {
                Millimeter result;
                result.value_ -= lhs.value_;

                return result;
            }

            friend Millimeter
            operator*(std::int32_t value, Millimeter p) {
                p *= value; return p;
            }

            friend Millimeter
            operator*(Millimeter p, std::int32_t value) {
                p *= value; return p;
            }

            friend Millimeter
            operator/(Millimeter p, std::int32_t value) {
                p /= value; return p;
            }

            friend std::ostream&
            operator<<(std::ostream& os, const Millimeter& p) {
                return os << static_cast<std::int32_t>(p.value_) << "mm";
            }

            explicit operator std::int32_t() const { return value_; }

            explicit operator Meter() const;
            explicit operator Decimeter() const;
            explicit operator Centimeter() const;
            explicit operator Micrometer() const;
        private:
            std::int32_t value_;
    };

    class Micrometer {
        public:
            Micrometer() : value_(0) {}
            Micrometer(std::int32_t value) : value_(value) {}

            Micrometer(const Meter& value);
            Micrometer(const Decimeter& value);
            Micrometer(const Centimeter& value);
            Micrometer(const Millimeter& value);

            friend std::strong_ordering
            operator<=>(const Micrometer& lhs, const Micrometer& rhs) {
                return lhs.value_ <=> rhs.value_;
            }

            friend bool operator==(const Micrometer& lhs, const Micrometer& rhs) = default;
            friend bool operator!=(const Micrometer& lhs, const Micrometer& rhs) = default;
            friend bool operator<(const Micrometer& lhs, const Micrometer& rhs) = default;
            friend bool operator<=(const Micrometer& lhs, const Micrometer& rhs) = default;
            friend bool operator>(const Micrometer& lhs, const Micrometer& rhs) = default;
            friend bool operator>=(const Micrometer& lhs, const Micrometer& rhs) = default;

            Micrometer&
            operator+=(const Micrometer& rhs) {
                value_ += rhs.value_; return *this;
            }

            Micrometer&
            operator-=(const Micrometer& rhs) {
                value_ -= rhs.value_; return *this;
            }

            Micrometer&
            operator*=(int32_t value) {
                value_ *= value;
                return *this;
            }

            Micrometer&
            operator/=(int32_t value) {
                value_ /= value;
                return *this;
            }

            friend Micrometer
            operator+(Micrometer lhs, const Micrometer& rhs) {
                lhs += rhs; return lhs;
            }

            friend Micrometer
            operator-(Micrometer lhs, const Micrometer& rhs) {
                lhs -= rhs; return lhs;
            }

            friend Micrometer
            operator-(const Micrometer& lhs) {
                Micrometer result;
                result.value_ -= lhs.value_;

                return result;
            }

            friend Micrometer
            operator*(std::int32_t value, Micrometer p) {
                p *= value; return p;
            }

            friend Micrometer
            operator*(Micrometer p, std::int32_t value) {
                p *= value; return p;
            }

            friend Micrometer
            operator/(Micrometer p, std::int32_t value) {
                p /= value; return p;
            }

            friend std::ostream&
            operator<<(std::ostream& os, const Micrometer& p) {
                return os << static_cast<std::int32_t>(p.value_) << "um";
            }

            explicit operator std::int32_t() const { return value_; }

            explicit operator Meter() const;
            explicit operator Decimeter() const;
            explicit operator Centimeter() const;
            explicit operator Millimeter() const;
        private:
            std::int32_t value_;
    };


    inline Decimeter::Decimeter(const Meter&      value) : value_(static_cast<std::int32_t>(value) * 1e1){}
    inline Decimeter::Decimeter(const Centimeter& value) : value_(static_cast<std::int32_t>(value) / 1e1){}
    inline Decimeter::Decimeter(const Millimeter& value) : value_(static_cast<std::int32_t>(value) / 1e2){}
    inline Decimeter::Decimeter(const Micrometer& value) : value_(static_cast<std::int32_t>(value) / 1e5){}

    inline Centimeter::Centimeter(const Meter&      value) : value_(static_cast<std::int32_t>(value) * 1e2){}
    inline Centimeter::Centimeter(const Decimeter&  value) : value_(static_cast<std::int32_t>(value) * 1e1){}
    inline Centimeter::Centimeter(const Millimeter& value) : value_(static_cast<std::int32_t>(value) / 1e1){}
    inline Centimeter::Centimeter(const Micrometer& value) : value_(static_cast<std::int32_t>(value) / 1e4){}

    inline Millimeter::Millimeter(const Meter&      value) : value_(static_cast<std::int32_t>(value) * 1e3){}
    inline Millimeter::Millimeter(const Decimeter&  value) : value_(static_cast<std::int32_t>(value) * 1e2){}
    inline Millimeter::Millimeter(const Centimeter& value) : value_(static_cast<std::int32_t>(value) * 1e1){}
    inline Millimeter::Millimeter(const Micrometer& value) : value_(static_cast<std::int32_t>(value) / 1e3){}

    inline Micrometer::Micrometer(const Meter&      value) : value_(static_cast<std::int32_t>(value) * 1e6){}
    inline Micrometer::Micrometer(const Decimeter&  value) : value_(static_cast<std::int32_t>(value) * 1e5){}
    inline Micrometer::Micrometer(const Centimeter& value) : value_(static_cast<std::int32_t>(value) * 1e4){}
    inline Micrometer::Micrometer(const Millimeter& value) : value_(static_cast<std::int32_t>(value) * 1e3){}

    inline Meter::operator Decimeter() const    { return Decimeter(*this); }
    inline Meter::operator Centimeter() const   { return Centimeter(*this); }
    inline Meter::operator Millimeter() const   { return Millimeter(*this); }
    inline Meter::operator Micrometer() const   { return Micrometer(*this); }

    inline Decimeter::operator Meter() const        { return Meter(*this); }
    inline Decimeter::operator Centimeter() const   { return Centimeter(*this); }
    inline Decimeter::operator Millimeter() const   { return Millimeter(*this); }
    inline Decimeter::operator Micrometer() const   { return Micrometer(*this); }

    inline Centimeter::operator Meter() const       { return Meter(*this); }
    inline Centimeter::operator Decimeter() const   { return Decimeter(*this); }
    inline Centimeter::operator Millimeter() const  { return Millimeter(*this); }
    inline Centimeter::operator Micrometer() const  { return Micrometer(*this); }

    inline Millimeter::operator Meter() const       { return Meter(*this); }
    inline Millimeter::operator Decimeter() const   { return Decimeter(*this); }
    inline Millimeter::operator Centimeter() const  { return Centimeter(*this); }
    inline Millimeter::operator Micrometer() const  { return Micrometer(*this); }

    inline Micrometer::operator Meter() const       { return Meter(*this); }
    inline Micrometer::operator Decimeter() const   { return Decimeter(*this); }
    inline Micrometer::operator Centimeter() const  { return Centimeter(*this); }
    inline Micrometer::operator Millimeter() const  { return Millimeter(*this); }
} // namespace dimension
} // namespace geometry
} // namespace paulista

#endif // PAULISTA_GEOMETRY_DIMENSION_HPP__
