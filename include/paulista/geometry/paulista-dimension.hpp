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
            Decimeter();
            Decimeter(std::int32_t value);

            Decimeter(const Meter& value);
            Decimeter(const Centimeter& value);
            Decimeter(const Millimeter& value);
            Decimeter(const Micrometer& value);

            friend std::strong_ordering
            operator<=>(const Decimeter& lhs, const Decimeter& rhs);

            friend bool operator==(const Decimeter& lhs, const Decimeter& rhs) = default;
            friend bool operator!=(const Decimeter& lhs, const Decimeter& rhs) = default;
            friend bool operator<(const Decimeter& lhs, const Decimeter& rhs) = default;
            friend bool operator<=(const Decimeter& lhs, const Decimeter& rhs) = default;
            friend bool operator>(const Decimeter& lhs, const Decimeter& rhs) = default;
            friend bool operator>=(const Decimeter& lhs, const Decimeter& rhs) = default;

            Decimeter& operator+=(const Decimeter& rhs);
            Decimeter& operator-=(const Decimeter& rhs);
            Decimeter& operator*=(int32_t value);
            Decimeter& operator/=(int32_t value);

            friend Decimeter operator+(Decimeter lhs, const Decimeter& rhs);
            friend Decimeter operator-(Decimeter lhs, const Decimeter& rhs);
            friend Decimeter operator-(const Decimeter& lhs);

            friend Decimeter operator*(std::int32_t value, Decimeter p);
            friend Decimeter operator*(Decimeter p, std::int32_t value);
            friend Decimeter operator/(Decimeter p, std::int32_t value);

            friend std::ostream&
            operator<<(std::ostream& os, const Decimeter& p);

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
            Centimeter();
            Centimeter(std::int32_t value);

            Centimeter(const Meter& value);
            Centimeter(const Decimeter& value);
            Centimeter(const Millimeter& value);
            Centimeter(const Micrometer& value);

            friend std::strong_ordering
            operator<=>(const Centimeter& lhs, const Centimeter& rhs);

            friend bool operator==(const Centimeter& lhs, const Centimeter& rhs) = default;
            friend bool operator!=(const Centimeter& lhs, const Centimeter& rhs) = default;
            friend bool operator<(const Centimeter& lhs, const Centimeter& rhs) = default;
            friend bool operator<=(const Centimeter& lhs, const Centimeter& rhs) = default;
            friend bool operator>(const Centimeter& lhs, const Centimeter& rhs) = default;
            friend bool operator>=(const Centimeter& lhs, const Centimeter& rhs) = default;

            Centimeter& operator+=(const Centimeter& rhs);
            Centimeter& operator-=(const Centimeter& rhs);
            Centimeter& operator*=(int32_t value);
            Centimeter& operator/=(int32_t value);

            friend Centimeter operator+(Centimeter lhs, const Centimeter& rhs);
            friend Centimeter operator-(Centimeter lhs, const Centimeter& rhs);
            friend Centimeter operator-(const Centimeter& lhs);

            friend Centimeter operator*(std::int32_t value, Centimeter p);
            friend Centimeter operator*(Centimeter p, std::int32_t value);
            friend Centimeter operator/(Centimeter p, std::int32_t value);

            friend std::ostream&
            operator<<(std::ostream& os, const Centimeter& p);

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
            Millimeter();
            Millimeter(std::int32_t value);

            Millimeter(const Meter& value);
            Millimeter(const Decimeter& value);
            Millimeter(const Centimeter& value);
            Millimeter(const Micrometer& value);

            friend std::strong_ordering
            operator<=>(const Millimeter& lhs, const Millimeter& rhs);

            friend bool operator==(const Millimeter& lhs, const Millimeter& rhs) = default;
            friend bool operator!=(const Millimeter& lhs, const Millimeter& rhs) = default;
            friend bool operator<(const Millimeter& lhs, const Millimeter& rhs) = default;
            friend bool operator<=(const Millimeter& lhs, const Millimeter& rhs) = default;
            friend bool operator>(const Millimeter& lhs, const Millimeter& rhs) = default;
            friend bool operator>=(const Millimeter& lhs, const Millimeter& rhs) = default;

            Millimeter& operator+=(const Millimeter& rhs);
            Millimeter& operator-=(const Millimeter& rhs);
            Millimeter& operator*=(int32_t value);
            Millimeter& operator/=(int32_t value);

            friend Millimeter operator+(Millimeter lhs, const Millimeter& rhs);
            friend Millimeter operator-(Millimeter lhs, const Millimeter& rhs);
            friend Millimeter operator-(const Millimeter& lhs);

            friend Millimeter operator*(std::int32_t value, Millimeter p);
            friend Millimeter operator*(Millimeter p, std::int32_t value);
            friend Millimeter operator/(Millimeter p, std::int32_t value);

            friend std::ostream&
            operator<<(std::ostream& os, const Millimeter& p);

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
            Micrometer();
            Micrometer(std::int32_t value);

            Micrometer(const Meter& value);
            Micrometer(const Decimeter& value);
            Micrometer(const Centimeter& value);
            Micrometer(const Millimeter& value);

            friend std::strong_ordering
            operator<=>(const Micrometer& lhs, const Micrometer& rhs);

            friend bool operator==(const Micrometer& lhs, const Micrometer& rhs) = default;
            friend bool operator!=(const Micrometer& lhs, const Micrometer& rhs) = default;
            friend bool operator<(const Micrometer& lhs, const Micrometer& rhs) = default;
            friend bool operator<=(const Micrometer& lhs, const Micrometer& rhs) = default;
            friend bool operator>(const Micrometer& lhs, const Micrometer& rhs) = default;
            friend bool operator>=(const Micrometer& lhs, const Micrometer& rhs) = default;

            Micrometer& operator+=(const Micrometer& rhs);
            Micrometer& operator-=(const Micrometer& rhs);
            Micrometer& operator*=(int32_t value);
            Micrometer& operator/=(int32_t value);

            friend Micrometer operator+(Micrometer lhs, const Micrometer& rhs);
            friend Micrometer operator-(Micrometer lhs, const Micrometer& rhs);
            friend Micrometer operator-(const Micrometer& lhs);

            friend Micrometer operator*(std::int32_t value, Micrometer p);
            friend Micrometer operator*(Micrometer p, std::int32_t value);
            friend Micrometer operator/(Micrometer p, std::int32_t value);

            friend std::ostream&
            operator<<(std::ostream& os, const Micrometer& p);

            explicit operator std::int32_t() const { return value_; }

            explicit operator Meter() const;
            explicit operator Decimeter() const;
            explicit operator Centimeter() const;
            explicit operator Millimeter() const;
        private:
            std::int32_t value_;
    };
} // namespace dimension
} // namespace geometry
} // namespace paulista

#endif // PAULISTA_GEOMETRY_DIMENSION_HPP__
