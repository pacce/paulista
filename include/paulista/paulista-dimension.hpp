#ifndef PAULISTA_DIMENSION_HPP__
#define PAULISTA_DIMENSION_HPP__

#include <cstdint>
#include <ostream>

namespace paulista {
namespace dimension {
    class Meter;
    class Decimeter;
    class Centimeter;
    class Millimeter;
    class Micrometer;

    class Meter {
        public:
            Meter() : value_(0) {}
            Meter(std::int8_t value) : value_(value) {}

            friend std::strong_ordering
            operator<=>(const Meter& lhs, const Meter& rhs) {
                return lhs.value_ <=> rhs.value_;
            }

            friend bool operator==(const Meter& lhs, const Meter& rhs) = default;
            friend bool operator!=(const Meter& lhs, const Meter& rhs) = default;
            friend bool operator<(const Meter& lhs, const Meter& rhs) = default;
            friend bool operator<=(const Meter& lhs, const Meter& rhs) = default;
            friend bool operator>(const Meter& lhs, const Meter& rhs) = default;
            friend bool operator>=(const Meter& lhs, const Meter& rhs) = default;

            Meter&
            operator+=(const Meter& rhs) {
                value_ += rhs.value_; return *this;
            }

            Meter&
            operator-=(const Meter& rhs) {
                value_ -= rhs.value_; return *this;
            }

            friend Meter
            operator+(Meter lhs, const Meter& rhs) {
                lhs += rhs; return lhs;
            }

            friend Meter
            operator-(Meter lhs, const Meter& rhs) {
                lhs -= rhs; return lhs;
            }

            friend Meter
            operator-(const Meter& lhs) {
                Meter result;
                result.value_ -= lhs.value_;

                return result;
            }

            friend std::ostream&
            operator<<(std::ostream& os, const Meter& p) {
                return os << static_cast<std::int32_t>(p.value_) << "m";
            }
        private:
            std::int8_t value_;
    };
} // namespace dimension
} // namespace paulista

#endif // PAULISTA_DIMENSION_HPP__
