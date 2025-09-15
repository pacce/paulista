#include <gtest/gtest.h>
#include <paulista/paulista.hpp>
#include <iostream>

using paulista::domain::element::Triangle;
using paulista::domain::Node;
using paulista::domain::Nodes;
using paulista::geometry::dimension::Meter;

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

TEST(TRIANGLE, REGULAR) {
    using Node      = Node<Meter>;

    Nodes<Meter> nodes = {
        Node(100, 100, 100),
        Node(100, 200, 100),
        Node(200, 100, 100),
        Node(100, 100, 200)
    };

    Triangle triangle{0, 1, 2};

    std::optional<Meter> actual     = triangle.area(nodes);
    std::optional<Meter> expected   = Meter(100 * 100 / 2);

    ASSERT_TRUE(actual);
    EXPECT_EQ(actual, expected);
}

TEST(TRIANGLE, BOUNDS) {
    using Node      = Node<Meter>;

    Nodes<Meter> nodes = {
        Node(0, 0, 0),
        Node(1, 1, 1)
    };
    Triangle triangle{0, 1, 2};

    EXPECT_FALSE(triangle.area(nodes));
}
int
main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
