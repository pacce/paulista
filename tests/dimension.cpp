#include <gtest/gtest.h>
#include <paulista/paulista.hpp>
#include <rapidcheck/gtest.h>

using paulista::dimension::Meter;
using paulista::dimension::Decimeter;
using paulista::dimension::Centimeter;
using paulista::dimension::Millimeter;
using paulista::dimension::Micrometer;

namespace rc {
    template<>
    struct Arbitrary<Meter> {
        static Gen<Meter>
        arbitrary() {
            return gen::construct<Meter>(gen::inRange(-10, 10));
        }
    };

    template<>
    struct Arbitrary<Decimeter> {
        static Gen<Decimeter>
        arbitrary() {
            return gen::construct<Decimeter>(gen::inRange(-100, 100));
        }
    };

    template<>
    struct Arbitrary<Centimeter> {
        static Gen<Centimeter>
        arbitrary() {
            return gen::construct<Centimeter>(gen::inRange(-1000, 1000));
        }
    };

    template<>
    struct Arbitrary<Millimeter> {
        static Gen<Millimeter>
        arbitrary() {
            return gen::construct<Millimeter>(gen::inRange(-10000, 10000));
        }
    };

    template<>
    struct Arbitrary<Micrometer> {
        static Gen<Micrometer>
        arbitrary() {
            return gen::construct<Micrometer>(gen::inRange(-100000, 100000));
        }
    };
}

TEST(METER, COMPARISON) {
    Meter zero;
    Meter one(1);

    ASSERT_EQ(zero, zero);
    ASSERT_EQ( one,  one);

    ASSERT_NE(zero,  one);
    ASSERT_LE(zero, zero);
    ASSERT_LE(zero,  one);
    ASSERT_LT(zero,  one);

    ASSERT_GE(zero, zero);
    ASSERT_GE( one, zero);
    ASSERT_GT( one, zero);
}

RC_GTEST_PROP(METER, ADD, (const Meter& x, const Meter& y)) {
    Meter zero;
    Meter successor(1);

    EXPECT_EQ(x + zero, x);         // NEUTRAL
    EXPECT_EQ(x + y, y + x);        // COMMUTATIVE
    EXPECT_NE(x + successor, x);    // SUCCESSOR
}

RC_GTEST_PROP(METER, SUBTRACT, (const Meter& x, const Meter& y)) {
    Meter zero;
    Meter successor(1);

    EXPECT_EQ(x - zero, x);     // NEUTRAL
    EXPECT_EQ(x - y, -(y - x)); // ANTICOMMUTATIVE
}

RC_GTEST_PROP(METER, MULTIPLICATION, (const Meter& x)) {
    Meter zero;

    EXPECT_EQ(x * 1, x);        // NEUTRAL
    EXPECT_EQ(1 * x, x);        // NEUTRAL
    EXPECT_EQ(x * 0, zero);     // ZERO
    EXPECT_EQ(x * 2, x + x);    // DOUBLE
    EXPECT_EQ(x * 3, 3 * x);    // COMMUTATIVE
}

RC_GTEST_PROP(METER, DIVISION, (const Meter& x)) {
    EXPECT_EQ(x / 1, x);
}

TEST(METER, CONVERSION) {
    Meter unit(1e0);

    EXPECT_EQ(1e0, static_cast<std::int32_t>(           unit ));
    EXPECT_EQ(1e1, static_cast<std::int32_t>( Decimeter(unit)));
    EXPECT_EQ(1e2, static_cast<std::int32_t>(Centimeter(unit)));
    EXPECT_EQ(1e3, static_cast<std::int32_t>(Millimeter(unit)));
    EXPECT_EQ(1e6, static_cast<std::int32_t>(Micrometer(unit)));
}

TEST(DECIMETER, COMPARISON) {
    Decimeter zero;
    Decimeter one(1);

    ASSERT_EQ(zero, zero);
    ASSERT_EQ( one,  one);

    ASSERT_NE(zero,  one);
    ASSERT_LE(zero, zero);
    ASSERT_LE(zero,  one);
    ASSERT_LT(zero,  one);

    ASSERT_GE(zero, zero);
    ASSERT_GE( one, zero);
    ASSERT_GT( one, zero);
}

RC_GTEST_PROP(DECIMETER, ADD, (const Decimeter& x, const Decimeter& y)) {
    Decimeter zero;
    Decimeter successor(1);

    EXPECT_EQ(x + zero, x);         // NEUTRAL
    EXPECT_EQ(x + y, y + x);        // COMMUTATIVE
    EXPECT_NE(x + successor, x);    // SUCCESSOR
}

RC_GTEST_PROP(DECIMETER, SUBTRACT, (const Decimeter& x, const Decimeter& y)) {
    Decimeter zero;
    Decimeter successor(1);

    EXPECT_EQ(x - zero, x);     // NEUTRAL
    EXPECT_EQ(x - y, -(y - x)); // ANTICOMMUTATIVE
}

RC_GTEST_PROP(DECIMETER, MULTIPLICATION, (const Decimeter& x)) {
    Decimeter zero;

    EXPECT_EQ(x * 1, x);        // NEUTRAL
    EXPECT_EQ(1 * x, x);        // NEUTRAL
    EXPECT_EQ(x * 0, zero);     // ZERO
    EXPECT_EQ(x * 2, x + x);    // DOUBLE
    EXPECT_EQ(x * 3, 3 * x);    // COMMUTATIVE
}

RC_GTEST_PROP(DECIMETER, DIVISION, (const Decimeter& x)) {
    EXPECT_EQ(x / 1, x);
}

TEST(DECIMETER, CONVERSION) {
    Decimeter unit(1e1);

    EXPECT_EQ(1e0, static_cast<std::int32_t>(     Meter(unit)));
    EXPECT_EQ(1e1, static_cast<std::int32_t>(           unit));
    EXPECT_EQ(1e2, static_cast<std::int32_t>(Centimeter(unit)));
    EXPECT_EQ(1e3, static_cast<std::int32_t>(Millimeter(unit)));
    EXPECT_EQ(1e6, static_cast<std::int32_t>(Micrometer(unit)));
}

TEST(CENTIMETER, COMPARISON) {
    Centimeter zero;
    Centimeter one(1);

    ASSERT_EQ(zero, zero);
    ASSERT_EQ( one,  one);

    ASSERT_NE(zero,  one);
    ASSERT_LE(zero, zero);
    ASSERT_LE(zero,  one);
    ASSERT_LT(zero,  one);

    ASSERT_GE(zero, zero);
    ASSERT_GE( one, zero);
    ASSERT_GT( one, zero);
}

RC_GTEST_PROP(CENTIMETER, ADD, (const Centimeter& x, const Centimeter& y)) {
    Centimeter zero;
    Centimeter successor(1);

    EXPECT_EQ(x + zero, x);         // NEUTRAL
    EXPECT_EQ(x + y, y + x);        // COMMUTATIVE
    EXPECT_NE(x + successor, x);    // SUCCESSOR
}

RC_GTEST_PROP(CENTIMETER, SUBTRACT, (const Centimeter& x, const Centimeter& y)) {
    Centimeter zero;
    Centimeter successor(1);

    EXPECT_EQ(x - zero, x);     // NEUTRAL
    EXPECT_EQ(x - y, -(y - x)); // ANTICOMMUTATIVE
}

RC_GTEST_PROP(CENTIMETER, MULTIPLICATION, (const Centimeter& x)) {
    Centimeter zero;

    EXPECT_EQ(x * 1, x);        // NEUTRAL
    EXPECT_EQ(1 * x, x);        // NEUTRAL
    EXPECT_EQ(x * 0, zero);     // ZERO
    EXPECT_EQ(x * 2, x + x);    // DOUBLE
    EXPECT_EQ(x * 3, 3 * x);    // COMMUTATIVE
}

RC_GTEST_PROP(CENTIMETER, DIVISION, (const Centimeter& x)) {
    EXPECT_EQ(x / 1, x);
}

TEST(CENTIMETER, CONVERSION) {
    Centimeter unit(1e2);

    EXPECT_EQ(1e0, static_cast<std::int32_t>(     Meter(unit)));
    EXPECT_EQ(1e1, static_cast<std::int32_t>( Decimeter(unit)));
    EXPECT_EQ(1e2, static_cast<std::int32_t>(            unit));
    EXPECT_EQ(1e3, static_cast<std::int32_t>(Millimeter(unit)));
    EXPECT_EQ(1e6, static_cast<std::int32_t>(Micrometer(unit)));
}

TEST(MILLIMETER, COMPARISON) {
    Millimeter zero;
    Millimeter one(1);

    ASSERT_EQ(zero, zero);
    ASSERT_EQ( one,  one);

    ASSERT_NE(zero,  one);
    ASSERT_LE(zero, zero);
    ASSERT_LE(zero,  one);
    ASSERT_LT(zero,  one);

    ASSERT_GE(zero, zero);
    ASSERT_GE( one, zero);
    ASSERT_GT( one, zero);
}

RC_GTEST_PROP(MILLIMETER, ADD, (const Millimeter& x, const Millimeter& y)) {
    Millimeter zero;
    Millimeter successor(1);

    EXPECT_EQ(x + zero, x);         // NEUTRAL
    EXPECT_EQ(x + y, y + x);        // COMMUTATIVE
    EXPECT_NE(x + successor, x);    // SUCCESSOR
}

RC_GTEST_PROP(MILLIMETER, SUBTRACT, (const Millimeter& x, const Millimeter& y)) {
    Millimeter zero;
    Millimeter successor(1);

    EXPECT_EQ(x - zero, x);     // NEUTRAL
    EXPECT_EQ(x - y, -(y - x)); // ANTICOMMUTATIVE
}

RC_GTEST_PROP(MILLIMETER, MULTIPLICATION, (const Millimeter& x)) {
    Millimeter zero;

    EXPECT_EQ(x * 1, x);        // NEUTRAL
    EXPECT_EQ(1 * x, x);        // NEUTRAL
    EXPECT_EQ(x * 0, zero);     // ZERO
    EXPECT_EQ(x * 2, x + x);    // DOUBLE
    EXPECT_EQ(x * 3, 3 * x);    // COMMUTATIVE
}

RC_GTEST_PROP(MILLIMETER, DIVISION, (const Millimeter& x)) {
    EXPECT_EQ(x / 1, x);
}

TEST(MILLIMETER, CONVERSION) {
    Millimeter unit(1e3);

    EXPECT_EQ(1e0, static_cast<std::int32_t>(     Meter(unit)));
    EXPECT_EQ(1e1, static_cast<std::int32_t>( Decimeter(unit)));
    EXPECT_EQ(1e2, static_cast<std::int32_t>(Centimeter(unit)));
    EXPECT_EQ(1e3, static_cast<std::int32_t>(            unit));
    EXPECT_EQ(1e6, static_cast<std::int32_t>(Micrometer(unit)));
}

TEST(MICROMETER, COMPARISON) {
    Micrometer zero;
    Micrometer one(1);

    ASSERT_EQ(zero, zero);
    ASSERT_EQ( one,  one);

    ASSERT_NE(zero,  one);
    ASSERT_LE(zero, zero);
    ASSERT_LE(zero,  one);
    ASSERT_LT(zero,  one);

    ASSERT_GE(zero, zero);
    ASSERT_GE( one, zero);
    ASSERT_GT( one, zero);
}

RC_GTEST_PROP(MICROMETER, ADD, (const Micrometer& x, const Micrometer& y)) {
    Micrometer zero;
    Micrometer successor(1);

    EXPECT_EQ(x + zero, x);         // NEUTRAL
    EXPECT_EQ(x + y, y + x);        // COMMUTATIVE
    EXPECT_NE(x + successor, x);    // SUCCESSOR
}

RC_GTEST_PROP(MICROMETER, SUBTRACT, (const Micrometer& x, const Micrometer& y)) {
    Micrometer zero;
    Micrometer successor(1);

    EXPECT_EQ(x - zero, x);     // NEUTRAL
    EXPECT_EQ(x - y, -(y - x)); // ANTICOMMUTATIVE
}

RC_GTEST_PROP(MICROMETER, MULTIPLICATION, (const Micrometer& x)) {
    Micrometer zero;

    EXPECT_EQ(x * 1, x);        // NEUTRAL
    EXPECT_EQ(1 * x, x);        // NEUTRAL
    EXPECT_EQ(x * 0, zero);     // ZERO
    EXPECT_EQ(x * 2, x + x);    // DOUBLE
    EXPECT_EQ(x * 3, 3 * x);    // COMMUTATIVE
}

RC_GTEST_PROP(MICROMETER, DIVISION, (const Micrometer& x)) {
    EXPECT_EQ(x / 1, x);
}

TEST(MICROMETER, CONVERSION) {
    Micrometer unit(1e6);

    EXPECT_EQ(1e0, static_cast<std::int32_t>(     Meter(unit)));
    EXPECT_EQ(1e1, static_cast<std::int32_t>( Decimeter(unit)));
    EXPECT_EQ(1e2, static_cast<std::int32_t>(Centimeter(unit)));
    EXPECT_EQ(1e3, static_cast<std::int32_t>(Millimeter(unit)));
    EXPECT_EQ(1e6, static_cast<std::int32_t>(            unit));
}

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
