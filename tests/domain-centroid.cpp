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
using paulista::geometry::dimension::Centimeter;
using paulista::geometry::tridimensional::Point;

TEST(TRIANGLE, SIMPLE) {
    using Node      = Node<Meter>;
    using Centroid  = Centroid<Meter>;

    Nodes<Meter> nodes = {
        Node(0, 0, 0),
        Node(3, 0, 0),
        Node(0, 3, 0)
    };

    Triangle triangle{0, 1, 2};

    std::optional<Centroid> actual      = triangle.centroid(nodes);
    std::optional<Centroid> expected    = Centroid(1, 1, 0);

    ASSERT_TRUE(actual);
    EXPECT_EQ(actual, expected);
}

TEST(TRIANGLE, INDICES) {
    using Node = Node<Meter>;

    Nodes<Meter> nodes = {
        Node(0, 0, 0),
        Node(3, 0, 0)
    };
    std::vector<Triangle> triangles = {
          Triangle{0, 1, 2}
        , Triangle{1, 2, 3}
    };
    for (const Triangle& triangle : triangles) {
        EXPECT_FALSE(triangle.centroid(nodes));
    }
}

TEST(TETRAHEDRON, SIMPLE) {
    using Node      = Node<Meter>;
    using Centroid  = Centroid<Meter>;

    Nodes<Meter> nodes = {
        Node(0, 0, 0),
        Node(4, 0, 0),
        Node(0, 4, 0),
        Node(0, 0, 4)
    };

    Tetrahedron tetrahedron{0, 1, 2, 3};

    std::optional<Centroid> actual      = tetrahedron.centroid(nodes);
    std::optional<Centroid> expected    = Centroid(1, 1, 1);

    ASSERT_TRUE(actual);
    EXPECT_EQ(actual, expected);
}

TEST(TETRAHEDRON, REGULAR) {
    using Node      = Node<Meter>;
    using Centroid  = Centroid<Meter>;

    Nodes<Meter> nodes = {
        Node( 1,  1,  1),
        Node(-1, -1,  1),
        Node(-1,  1, -1),
        Node( 1, -1, -1)
    };

    Tetrahedron tetrahedron{0, 1, 2, 3};

    std::optional<Centroid> actual      = tetrahedron.centroid(nodes);
    std::optional<Centroid> expected    = Centroid(0, 0, 0);

    ASSERT_TRUE(actual);
    EXPECT_EQ(actual, expected);
}

TEST(TETRAHEDRON, BOUNDS) {
    using Node = Node<Meter>;

    Nodes<Meter> nodes = {
        Node(0, 0, 0),
        Node(4, 0, 0),
        Node(0, 4, 0)
    };
    std::vector<Tetrahedron> tetrahedrons = {
          Tetrahedron{0, 1, 2, 3}
        , Tetrahedron{1, 2, 3, 4}
        , Tetrahedron{0, 1, 4, 5}
    };

    for (const Tetrahedron& tetrahedron : tetrahedrons) {
        EXPECT_FALSE(tetrahedron.centroid(nodes));
    }
}

TEST(DOMAIN, TRIANGLE) {
    using Node = Node<Meter>;
    using Domain = paulista::Domain<Meter>;

    Domain domain;
    domain.nodes = {
        Node(0, 0, 0),
        Node(3, 0, 0),
        Node(0, 3, 0)
    };
    domain.elements = {
        Triangle{0, 1, 2}
    };

    std::vector<std::optional<Node>> actual     = domain.centroids();
    std::vector<std::optional<Node>> expected   = {Node(1, 1, 0)};

    ASSERT_EQ(actual.size(), expected.size());
    for (std::size_t i = 0; i < expected.size(); i++) {
        EXPECT_EQ(actual[i], expected[i]);
    }
}

TEST(DOMAIN, TETRAHEDRON) {
    using Node = Node<Meter>;
    using Domain = paulista::Domain<Meter>;

    Domain domain;
    domain.nodes = {
        Node(0, 0, 0),
        Node(4, 0, 0),
        Node(0, 4, 0),
        Node(0, 0, 4)
    };
    domain.elements = {
        Tetrahedron{0, 1, 2, 3}
    };

    std::vector<std::optional<Node>> actual     = domain.centroids();
    std::vector<std::optional<Node>> expected   = {Node(1, 1, 1)};

    ASSERT_EQ(actual.size(), expected.size());
    for (std::size_t i = 0; i < expected.size(); i++) {
        EXPECT_EQ(actual[i], expected[i]);
    }
}

TEST(DOMAIN, MIXED) {
    using Node      = Node<Meter>;
    using Domain    = paulista::Domain<Meter>;

    Domain domain;
    domain.nodes = {
        Node(  0,   0,   0),  // 0
        Node(300,   0,   0),  // 1
        Node(  0, 300,   0),  // 2
        Node(  0,   0, 300)   // 3
    };
    domain.elements = {
        Triangle{0, 1, 2},        // Centroid: (1, 1, 0)
        Tetrahedron{0, 1, 2, 3}   // Centroid: (0.75, 0.75, 0.75)
    };

    std::vector<std::optional<Node>> actual     = domain.centroids();
    std::vector<std::optional<Node>> expected   = {
          Node(100, 100,   0)
        , Node( 75,  75,  75)
    };
    ASSERT_EQ(actual.size(), expected.size());
    for (std::size_t i = 0; i < expected.size(); i++) {
        EXPECT_EQ(*actual[i], *expected[i]);
    }
}

TEST(DOMAIN, INDICES) {
    using Node      = Node<Meter>;
    using Domain    = paulista::Domain<Meter>;

    Domain domain;
    domain.nodes = {
        Node(0, 0, 0),
        Node(3, 0, 0)
    };
    domain.elements = {
        Triangle{0, 1, 2},        // Index 2 out of bounds
        Triangle{0, 1, 3},        // Index 3 out of bounds
        Tetrahedron{0, 1, 2, 3}   // Indices 2,3 out of bounds
    };

    std::vector<std::optional<Node>> actual     = domain.centroids();
    std::vector<std::optional<Node>> expected   = {std::nullopt, std::nullopt, std::nullopt};

    ASSERT_EQ(actual.size(), expected.size());
    for (std::size_t i = 0; i < expected.size(); i++) {
        EXPECT_EQ(actual[i], expected[i]);
    }
}

TEST(DOMAIN, EMPTY) {
    using Node      = Node<Meter>;
    using Domain    = paulista::Domain<Meter>;
    
    Domain domain;
    std::vector<std::optional<Node>> actual = domain.centroids();
    EXPECT_TRUE(actual.empty());
}

int
main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
