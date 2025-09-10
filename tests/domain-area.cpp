#include <gtest/gtest.h>
#include <paulista/paulista.hpp>

using paulista::domain::Element;
using paulista::domain::Elements;
using paulista::domain::element::Triangle;
using paulista::domain::element::Tetrahedron;
using paulista::domain::Centroid;
using paulista::domain::Node;
using paulista::domain::Nodes;

using paulista::geometry::dimension::Meter;
using paulista::geometry::tridimensional::Point;

TEST(TRIANGLE, SIMPLE) {
    using Node      = Node<Meter>;

    Nodes<Meter> nodes = {
        Node(  0,   0,   0),
        Node(100,   0,   0),
        Node(  0, 100,   0)
    };

    Triangle triangle{0, 1, 2};

    std::optional<Meter> actual     = triangle.area(nodes);
    std::optional<Meter> expected   = Meter(100 * 100 / 2);

    ASSERT_TRUE(actual);
    EXPECT_EQ(actual, expected);
}

int
main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
