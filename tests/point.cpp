#include <gtest/gtest.h>
#include <paulista/paulista.hpp>
#include <rapidcheck/gtest.h>

using Millimeter    = paulista::geometry::dimension::Millimeter;
using Point         = paulista::geometry::tridimensional::Point<Millimeter>;

namespace rc {
    template<>
    struct Arbitrary<Point> {
        static Gen<Point>
        arbitrary() {
            return gen::construct<Point>(
                      gen::inRange(-1000, 1000)
                    , gen::inRange(-1000, 1000)
                    , gen::inRange(-1000, 1000)
                    );
        }
    };
}

RC_GTEST_PROP(ADD, NEUTRAL, (const Point& xs)) {
    Point zero;
    EXPECT_EQ(xs + zero, xs);
}

RC_GTEST_PROP(ADD, COMMUTATIVE, (const Point& xs, const Point& ys)) {
    EXPECT_EQ(xs + ys, ys + xs);
}

RC_GTEST_PROP(ADD, SUCCESSOR, (const Point& xs)) {
    EXPECT_NE(xs + Point(1, 0, 0), xs);
    EXPECT_NE(xs + Point(0, 1, 0), xs);
    EXPECT_NE(xs + Point(0, 0, 1), xs);

    EXPECT_NE(xs + Point(1, 1, 0), xs);
    EXPECT_NE(xs + Point(1, 0, 1), xs);
    EXPECT_NE(xs + Point(0, 1, 1), xs);

    EXPECT_NE(xs + Point(1, 1, 1), xs);
}

RC_GTEST_PROP(SUBTRACT, NEUTRAL, (const Point& xs)) {
    Point zero;
    EXPECT_EQ(xs - zero, xs);
}

RC_GTEST_PROP(SUBTRACT, ANTICOMMUTATIVE, (const Point& xs, const Point& ys)) {
    EXPECT_EQ(xs - ys, -(ys - xs));
}

RC_GTEST_PROP(MULTIPLICATION, NEUTRAL, (const Point& xs)) {
    EXPECT_EQ(xs * 1, xs);
    EXPECT_EQ(1 * xs, xs);
}

RC_GTEST_PROP(MULTIPLICATION, ZERO, (const Point& xs)) {
    Point zero;
    EXPECT_EQ(xs * 0, zero);
}

RC_GTEST_PROP(MULTIPLICATION, DOUBLE, (const Point& xs)) {
    EXPECT_EQ(xs * 2, xs + xs);
}

RC_GTEST_PROP(MULTIPLICATION, COMMUTATIVE, (const Point& xs, std::uint8_t v)) {
    EXPECT_EQ(xs * v, v * xs);
}

RC_GTEST_PROP(DIVISION, NEUTRAL, (const Point& xs)) {
    EXPECT_EQ(xs / 1, xs);
}

TEST(DOT, D1) {
    Point x(1, 0, 0);
    Point y(0, 1, 0);
    Point z(0, 0, 1);

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
    Point xy(1, 1, 0);
    Point yz(0, 1, 1);
    Point xz(1, 0, 1);

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
    Point xyz(1, 1, 1);
    EXPECT_EQ(xyz.dot(xyz), 3);
}

RC_GTEST_PROP(DOT, COMMUTATIVE, (const Point& xs, const Point& ys)) {
    EXPECT_EQ(xs.dot(ys), ys.dot(xs));
}

RC_GTEST_PROP(DOT, SCALAR, (const Point& xs, const Point& ys, std::uint8_t value)) {
    EXPECT_EQ((value * xs).dot(ys), value * (xs.dot(ys)));
    EXPECT_EQ((value * xs).dot(ys),   xs.dot(value * ys));
}

TEST(NORM, D1) {
    Point x(1, 0, 0);
    Point y(0, 1, 0);
    Point z(0, 0, 1);

    EXPECT_EQ(x.norm(), Millimeter(1));
    EXPECT_EQ(y.norm(), Millimeter(1));
    EXPECT_EQ(z.norm(), Millimeter(1));
}

TEST(NORM, D2) {
    Point xy(100, 100,   0);
    Point yz(  0, 100, 100);
    Point xz(100,   0, 100);

    using paulista::geometry::dimension::sqrt;
    EXPECT_EQ(xy.norm(), Millimeter(141));
    EXPECT_EQ(yz.norm(), Millimeter(141));
    EXPECT_EQ(xz.norm(), Millimeter(141));
}

TEST(NORM, D3) {
    Point xyz(100, 100, 100);
    using paulista::geometry::dimension::sqrt;
    EXPECT_EQ(xyz.norm(), Millimeter(173));
}

TEST(NORM, ZERO) {
    Point zero(0, 0, 0);
    EXPECT_EQ(zero.norm(), Millimeter(0));
}

TEST(NORM, SCALING) {
    Point x(3, 0, 0);
    Point y(0, 4, 0);
    Point z(0, 0, 5);

    EXPECT_EQ(x.norm(), Millimeter(3));
    EXPECT_EQ(y.norm(), Millimeter(4));
    EXPECT_EQ(z.norm(), Millimeter(5));

    Point pythagorean(3, 4, 0);
    EXPECT_EQ(pythagorean.norm(), Millimeter(5));
}

TEST(CROSS, D1) {
    Point x(1, 0, 0);
    Point y(0, 1, 0);
    Point z(0, 0, 1);

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

RC_GTEST_PROP(CENTROID, SINGLE, (const Point& xs)) {
    std::optional<Point> c = paulista::geometry::tridimensional::point::centroid<Millimeter>({xs});
    ASSERT_TRUE(c);
    EXPECT_EQ(c, xs);
}

RC_GTEST_PROP(CENTROID, CONSTANT, (const Point& xs, std::uint8_t size)) {
    RC_PRE(size > 0);

    std::optional<Point> c = paulista::geometry::tridimensional::point::centroid<Millimeter>({size, xs});
    ASSERT_TRUE(c);
    EXPECT_EQ(c, xs);
}

RC_GTEST_PROP(CENTROID, PROGRESSION, (std::uint8_t size)) {
    RC_PRE(size > 0);

    std::vector<Point> ps;
    for (std::int32_t i = 0; i < size; i++) {
        ps.emplace_back(i, i, i);
    }
    Point mean = (ps.front() + ps.back()) / 2;

    EXPECT_EQ(mean, paulista::geometry::tridimensional::point::centroid(ps));
}

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
