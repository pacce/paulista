#include <gtest/gtest.h>
#include <paulista/paulista.hpp>
#include <rapidcheck/gtest.h>

using Millimeter    = paulista::geometry::dimension::Millimeter;
using P2            = paulista::geometry::bidimensional::Point<Millimeter>;
using P3            = paulista::geometry::tridimensional::Point<Millimeter>;

namespace rc {
    template<>
    struct Arbitrary<P2> {
        static Gen<P2>
        arbitrary() {
            return gen::construct<P2>(
                      gen::inRange(-1000, 1000)
                    , gen::inRange(-1000, 1000)
                    );
        }
    };

    template<>
    struct Arbitrary<P3> {
        static Gen<P3>
        arbitrary() {
            return gen::construct<P3>(
                      gen::inRange(-1000, 1000)
                    , gen::inRange(-1000, 1000)
                    , gen::inRange(-1000, 1000)
                    );
        }
    };
}

namespace bidimensional {
RC_GTEST_PROP(ADD, NEUTRAL, (const P2& xs)) {
    P2 zero;
    EXPECT_EQ(xs + zero, xs);
}

RC_GTEST_PROP(ADD, COMMUTATIVE, (const P2& xs, const P2& ys)) {
    EXPECT_EQ(xs + ys, ys + xs);
}

RC_GTEST_PROP(ADD, SUCCESSOR, (const P2& xs)) {
    EXPECT_NE(xs + P2(1, 0), xs);
    EXPECT_NE(xs + P2(0, 1), xs);

    EXPECT_NE(xs + P2(1, 1), xs);
    EXPECT_NE(xs + P2(1, 0), xs);
    EXPECT_NE(xs + P2(0, 1), xs);

    EXPECT_NE(xs + P2(1, 1), xs);
}

RC_GTEST_PROP(SUBTRACT, NEUTRAL, (const P2& xs)) {
    P2 zero;
    EXPECT_EQ(xs - zero, xs);
}

RC_GTEST_PROP(SUBTRACT, ANTICOMMUTATIVE, (const P2& xs, const P2& ys)) {
    EXPECT_EQ(xs - ys, -(ys - xs));
}

RC_GTEST_PROP(MULTIPLICATION, NEUTRAL, (const P2& xs)) {
    EXPECT_EQ(xs * 1, xs);
    EXPECT_EQ(1 * xs, xs);
}

RC_GTEST_PROP(MULTIPLICATION, ZERO, (const P2& xs)) {
    P2 zero;
    EXPECT_EQ(xs * 0, zero);
}

RC_GTEST_PROP(MULTIPLICATION, DOUBLE, (const P2& xs)) {
    EXPECT_EQ(xs * 2, xs + xs);
}

RC_GTEST_PROP(MULTIPLICATION, COMMUTATIVE, (const P2& xs, std::uint8_t v)) {
    EXPECT_EQ(xs * v, v * xs);
}

RC_GTEST_PROP(DIVISION, NEUTRAL, (const P2& xs)) {
    EXPECT_EQ(xs / 1, xs);
}

TEST(DOT, D1) {
    P2 x(1, 0);
    P2 y(0, 1);

    EXPECT_EQ(x.dot(x), 1);
    EXPECT_EQ(x.dot(y), 0);

    EXPECT_EQ(y.dot(x), 0);
    EXPECT_EQ(y.dot(y), 1);
}

TEST(DOT, D2) {
    P2 xy(1, 1);
    EXPECT_EQ(xy.dot(xy), 2);
}

RC_GTEST_PROP(DOT, COMMUTATIVE, (const P2& xs, const P2& ys)) {
    EXPECT_EQ(xs.dot(ys), ys.dot(xs));
}

RC_GTEST_PROP(DOT, SCALAR, (const P2& xs, const P2& ys, std::uint8_t value)) {
    EXPECT_EQ((value * xs).dot(ys), value * (xs.dot(ys)));
    EXPECT_EQ((value * xs).dot(ys),   xs.dot(value * ys));
}

TEST(NORM, D1) {
    P2 x(1, 0);
    P2 y(0, 1);

    EXPECT_EQ(x.norm(), Millimeter(1));
    EXPECT_EQ(y.norm(), Millimeter(1));
}

TEST(NORM, D2) {
    P2 xy(100, 100);

    EXPECT_EQ(xy.norm(), Millimeter(141));
}

TEST(NORM, ZERO) {
    P2 zero(0, 0);
    EXPECT_EQ(zero.norm(), Millimeter(0));
}

TEST(NORM, SCALING) {
    P2 x(3, 0);
    P2 y(0, 4);

    EXPECT_EQ(x.norm(), Millimeter(3));
    EXPECT_EQ(y.norm(), Millimeter(4));

    P2 pythagorean(3, 4);
    EXPECT_EQ(pythagorean.norm(), Millimeter(5));
}

TEST(CROSS, D1) {
    P2 x(1, 0);
    P2 y(0, 1);

    EXPECT_EQ(x.cross(y),  1);
    EXPECT_EQ(y.cross(x), -1);
}

TEST(CENTROID, EMPTY) {
    EXPECT_FALSE(paulista::geometry::bidimensional::point::centroid<Millimeter>({}));
}

RC_GTEST_PROP(CENTROID, SINGLE, (const P2& xs)) {
    std::optional<P2> c = paulista::geometry::bidimensional::point::centroid<Millimeter>({xs});
    ASSERT_TRUE(c);
    EXPECT_EQ(c, xs);
}

RC_GTEST_PROP(CENTROID, CONSTANT, (const P2& xs, std::uint8_t size)) {
    RC_PRE(size > 0);

    std::optional<P2> c = paulista::geometry::bidimensional::point::centroid<Millimeter>({size, xs});
    ASSERT_TRUE(c);
    EXPECT_EQ(c, xs);
}

RC_GTEST_PROP(CENTROID, PROGRESSION, (std::uint8_t size)) {
    RC_PRE(size > 0);

    std::vector<P2> ps;
    for (std::int32_t i = 0; i < size; i++) {
        ps.emplace_back(i, i);
    }
    P2 mean = (ps.front() + ps.back()) / 2;

    EXPECT_EQ(mean, paulista::geometry::bidimensional::point::centroid(ps));
}
} // namespace bidimensional

namespace tridimensional {
RC_GTEST_PROP(ADD, NEUTRAL, (const P3& xs)) {
    P3 zero;
    EXPECT_EQ(xs + zero, xs);
}

RC_GTEST_PROP(ADD, COMMUTATIVE, (const P3& xs, const P3& ys)) {
    EXPECT_EQ(xs + ys, ys + xs);
}

RC_GTEST_PROP(ADD, SUCCESSOR, (const P3& xs)) {
    EXPECT_NE(xs + P3(1, 0, 0), xs);
    EXPECT_NE(xs + P3(0, 1, 0), xs);
    EXPECT_NE(xs + P3(0, 0, 1), xs);

    EXPECT_NE(xs + P3(1, 1, 0), xs);
    EXPECT_NE(xs + P3(1, 0, 1), xs);
    EXPECT_NE(xs + P3(0, 1, 1), xs);

    EXPECT_NE(xs + P3(1, 1, 1), xs);
}

RC_GTEST_PROP(SUBTRACT, NEUTRAL, (const P3& xs)) {
    P3 zero;
    EXPECT_EQ(xs - zero, xs);
}

RC_GTEST_PROP(SUBTRACT, ANTICOMMUTATIVE, (const P3& xs, const P3& ys)) {
    EXPECT_EQ(xs - ys, -(ys - xs));
}

RC_GTEST_PROP(MULTIPLICATION, NEUTRAL, (const P3& xs)) {
    EXPECT_EQ(xs * 1, xs);
    EXPECT_EQ(1 * xs, xs);
}

RC_GTEST_PROP(MULTIPLICATION, ZERO, (const P3& xs)) {
    P3 zero;
    EXPECT_EQ(xs * 0, zero);
}

RC_GTEST_PROP(MULTIPLICATION, DOUBLE, (const P3& xs)) {
    EXPECT_EQ(xs * 2, xs + xs);
}

RC_GTEST_PROP(MULTIPLICATION, COMMUTATIVE, (const P3& xs, std::uint8_t v)) {
    EXPECT_EQ(xs * v, v * xs);
}

RC_GTEST_PROP(DIVISION, NEUTRAL, (const P3& xs)) {
    EXPECT_EQ(xs / 1, xs);
}

TEST(DOT, D1) {
    P3 x(1, 0, 0);
    P3 y(0, 1, 0);
    P3 z(0, 0, 1);

    EXPECT_EQ(x.dot(x), 1);
    EXPECT_EQ(x.dot(y), 0);
    EXPECT_EQ(x.dot(z), 0);

    EXPECT_EQ(y.dot(x), 0);
    EXPECT_EQ(y.dot(y), 1);
    EXPECT_EQ(y.dot(z), 0);

    EXPECT_EQ(z.dot(x), 0);
    EXPECT_EQ(z.dot(y), 0);
    EXPECT_EQ(z.dot(z), 1);
}

TEST(DOT, D2) {
    P3 xy(1, 1, 0);
    P3 yz(0, 1, 1);
    P3 xz(1, 0, 1);

    EXPECT_EQ(xy.dot(xy), 2);
    EXPECT_EQ(xy.dot(yz), 1);
    EXPECT_EQ(xy.dot(xz), 1);

    EXPECT_EQ(yz.dot(xy), 1);
    EXPECT_EQ(yz.dot(yz), 2);
    EXPECT_EQ(yz.dot(xz), 1);

    EXPECT_EQ(xz.dot(xy), 1);
    EXPECT_EQ(xz.dot(yz), 1);
    EXPECT_EQ(xz.dot(xz), 2);
}

TEST(DOT, D3) {
    P3 xyz(1, 1, 1);
    EXPECT_EQ(xyz.dot(xyz), 3);
}

RC_GTEST_PROP(DOT, COMMUTATIVE, (const P3& xs, const P3& ys)) {
    EXPECT_EQ(xs.dot(ys), ys.dot(xs));
}

RC_GTEST_PROP(DOT, SCALAR, (const P3& xs, const P3& ys, std::uint8_t value)) {
    EXPECT_EQ((value * xs).dot(ys), value * (xs.dot(ys)));
    EXPECT_EQ((value * xs).dot(ys),   xs.dot(value * ys));
}

TEST(NORM, D1) {
    P3 x(1, 0, 0);
    P3 y(0, 1, 0);
    P3 z(0, 0, 1);

    EXPECT_EQ(x.norm(), Millimeter(1));
    EXPECT_EQ(y.norm(), Millimeter(1));
    EXPECT_EQ(z.norm(), Millimeter(1));
}

TEST(NORM, D2) {
    P3 xy(100, 100,   0);
    P3 yz(  0, 100, 100);
    P3 xz(100,   0, 100);

    using paulista::geometry::dimension::sqrt;
    EXPECT_EQ(xy.norm(), Millimeter(141));
    EXPECT_EQ(yz.norm(), Millimeter(141));
    EXPECT_EQ(xz.norm(), Millimeter(141));
}

TEST(NORM, D3) {
    P3 xyz(100, 100, 100);
    using paulista::geometry::dimension::sqrt;
    EXPECT_EQ(xyz.norm(), Millimeter(173));
}

TEST(NORM, ZERO) {
    P3 zero(0, 0, 0);
    EXPECT_EQ(zero.norm(), Millimeter(0));
}

TEST(NORM, SCALING) {
    P3 x(3, 0, 0);
    P3 y(0, 4, 0);
    P3 z(0, 0, 5);

    EXPECT_EQ(x.norm(), Millimeter(3));
    EXPECT_EQ(y.norm(), Millimeter(4));
    EXPECT_EQ(z.norm(), Millimeter(5));

    P3 pythagorean(3, 4, 0);
    EXPECT_EQ(pythagorean.norm(), Millimeter(5));
}

TEST(CROSS, D1) {
    P3 x(1, 0, 0);
    P3 y(0, 1, 0);
    P3 z(0, 0, 1);

    EXPECT_EQ(x.cross(y), z);
    EXPECT_EQ(y.cross(z), x);
    EXPECT_EQ(z.cross(x), y);

    EXPECT_EQ(y.cross(x), -z);
    EXPECT_EQ(z.cross(y), -x);
    EXPECT_EQ(x.cross(z), -y);
}

TEST(CENTROID, EMPTY) {
    EXPECT_FALSE(paulista::geometry::tridimensional::point::centroid<Millimeter>({}));
}

RC_GTEST_PROP(CENTROID, SINGLE, (const P3& xs)) {
    std::optional<P3> c = paulista::geometry::tridimensional::point::centroid<Millimeter>({xs});
    ASSERT_TRUE(c);
    EXPECT_EQ(c, xs);
}

RC_GTEST_PROP(CENTROID, CONSTANT, (const P3& xs, std::uint8_t size)) {
    RC_PRE(size > 0);

    std::optional<P3> c = paulista::geometry::tridimensional::point::centroid<Millimeter>({size, xs});
    ASSERT_TRUE(c);
    EXPECT_EQ(c, xs);
}

RC_GTEST_PROP(CENTROID, PROGRESSION, (std::uint8_t size)) {
    RC_PRE(size > 0);

    std::vector<P3> ps;
    for (std::int32_t i = 0; i < size; i++) {
        ps.emplace_back(i, i, i);
    }
    P3 mean = (ps.front() + ps.back()) / 2;

    EXPECT_EQ(mean, paulista::geometry::tridimensional::point::centroid(ps));
}
} // namespace tridimensional


int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
