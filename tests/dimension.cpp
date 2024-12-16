#include <gtest/gtest.h>
#include <paulista/paulista.hpp>
#include <rapidcheck/gtest.h>

using paulista::dimension::Meter;

namespace rc {
    template<>
    struct Arbitrary<Meter> {
        static Gen<Meter>
        arbitrary() {
            return gen::construct<Meter>(gen::inRange(-10, 10));
        }
    };
}

TEST(COMPARISON, _) {
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

RC_GTEST_PROP(ADD, NEUTRAL, (const Meter& xs)) {
    Meter zero;
    EXPECT_EQ(xs + zero, xs);
}

RC_GTEST_PROP(ADD, COMMUTATIVE, (const Meter& xs, const Meter& ys)) {
    EXPECT_EQ(xs + ys, ys + xs);
}

RC_GTEST_PROP(ADD, SUCCESSOR, (const Meter& xs)) {
    EXPECT_NE(xs + Meter(1), xs);
}

RC_GTEST_PROP(SUBTRACT, NEUTRAL, (const Meter& xs)) {
    Meter zero;
    EXPECT_EQ(xs - zero, xs);
}

RC_GTEST_PROP(SUBTRACT, ANTICOMMUTATIVE, (const Meter& xs, const Meter& ys)) {
    EXPECT_EQ(xs - ys, -(ys - xs));
}

RC_GTEST_PROP(MULTIPLICATION, NEUTRAL, (const Meter& xs)) {
    EXPECT_EQ(xs * 1, xs);
    EXPECT_EQ(1 * xs, xs);
}

RC_GTEST_PROP(MULTIPLICATION, ZERO, (const Meter& xs)) {
    Meter zero;
    EXPECT_EQ(xs * 0, zero);
}

RC_GTEST_PROP(MULTIPLICATION, DOUBLE, (const Meter& xs)) {
    EXPECT_EQ(xs * 2, xs + xs);
}

RC_GTEST_PROP(MULTIPLICATION, COMMUTATIVE, (const Meter& xs, std::uint8_t v)) {
    EXPECT_EQ(xs * v, v * xs);
}

RC_GTEST_PROP(DIVISION, NEUTRAL, (const Meter& xs)) {
    EXPECT_EQ(xs / 1, xs);
}

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
