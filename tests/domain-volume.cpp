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

TEST(TETRAHEDRON, SIMPLE) {
    using Node      = Node<Meter>;

    Nodes<Meter> nodes = {
        Node(  0,   0,   0),
        Node(100,   0,   0),
        Node(  0, 100,   0),
        Node(  0,   0, 100)
    };

    Tetrahedron tetrahedron{0, 1, 2, 3};

    std::optional<Meter> actual     = tetrahedron.volume(nodes);
    std::optional<Meter> expected   = Meter(100 * 100 * 100 / 6);

    ASSERT_TRUE(actual);
    EXPECT_EQ(actual, expected);
}

TEST(TETRAHEDRON, REGULAR) {
    using Node      = Node<Meter>;

    Nodes<Meter> nodes = {
        Node(100, 100, 100),
        Node(100, 200, 100),
        Node(200, 100, 100),
        Node(100, 100, 200)
    };

    Tetrahedron tetrahedron{0, 1, 2, 3};

    std::optional<Meter> actual     = tetrahedron.volume(nodes);
    std::optional<Meter> expected   = Meter(100 * 100 * 100 / 6);

    ASSERT_TRUE(actual);
    EXPECT_EQ(actual, expected);
}

TEST(TETRAHEDRON, BOUNDS) {
    using Node      = Node<Meter>;

    Nodes<Meter> nodes = {
        Node(0, 0, 0),
        Node(1, 1, 1)
    };
    Tetrahedron tetrahedron{0, 1, 2, 3};

    EXPECT_FALSE(tetrahedron.volume(nodes));
}

int
main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
