#include <gtest/gtest.h>
#include <paulista/paulista.hpp>
#include <rapidcheck/gtest.h>

using paulista::tridimensional::Point;

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

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}