#include <gtest/gtest.h>
#include <paulista/paulista.hpp>

using paulista::Element;
using paulista::element::Triangle;
using paulista::element::is_triangle;
using paulista::element::is_tetrahedron;

using paulista::domain::Centroid;
using paulista::domain::Node;
using paulista::domain::Nodes;

using paulista::geometry::dimension::Meter;
using paulista::geometry::dimension::Millimeter;

using paulista::stiffness::Triplets;

TEST(AREA, SIMPLE) {
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

TEST(AREA, REGULAR) {
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

TEST(AREA, BOUNDS) {
    using Node      = Node<Meter>;

    Nodes<Meter> nodes = {
        Node(0, 0, 0),
        Node(1, 1, 1)
    };
    Triangle triangle{0, 1, 2};

    EXPECT_FALSE(triangle.area(nodes));
}

TEST(CENTROID, SIMPLE) {
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

TEST(CENTROID, INDICES) {
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


TEST(VISITOR, TRIANGLE) {
    Element triangle = Triangle{0, 1, 2};
    
    EXPECT_TRUE (std::visit(is_triangle, triangle));
}

TEST(VISITOR, TETRAHEDRON) {
    Element triangle = Triangle{0, 1, 2};
    EXPECT_FALSE(std::visit(is_tetrahedron, triangle));
}

TEST(STIFFNESS, EMPTY) {
    Triangle triangle{0, 1, 2};
    Nodes<Meter> nodes;

    EXPECT_FALSE(paulista::stiffness::triangle::local(triangle, nodes, 1.0f));
}

TEST(STIFFNESS, INDICES) {
    using Node  = Node<Meter>;
    using Nodes = Nodes<Meter>;

    Triangle triangle{0, 1, 5};
    Nodes nodes = {
        Node{0, 0, 0},
        Node{1, 0, 0},
        Node{0, 1, 0}
    };

    EXPECT_FALSE(paulista::stiffness::triangle::local(triangle, nodes, 1.0f));
}

TEST(STIFFNESS, RIGHT) {
    using Node  = Node<Millimeter>;
    using Nodes = Nodes<Millimeter>;

    Triangle triangle{0, 1, 2};
    Nodes nodes = {
        Node{   0,    0,    0},
        Node{1000,    0,    0},
        Node{   0, 1000,    0}
    };

    std::optional<Triplets<float>> result = paulista::stiffness::triangle::local(triangle, nodes, 1.0f);
    Triplets<float> expected = {
          {0, 0,  2.0f}
        , {0, 1,  1.0f}
        , {0, 2, -1.0f}
        , {1, 0,  1.0f}
        , {1, 1,  1.0f}
        , {1, 2,  0.0f}
        , {2, 0, -1.0f}
        , {2, 1,  0.0f}
        , {2, 2,  1.0f}
    };
    ASSERT_TRUE(result);
    ASSERT_EQ(result->size(), expected.size());

    for (std::size_t i = 0; i < 9; i++) {
        EXPECT_EQ((*result)[i].row, expected[i].row);
        EXPECT_EQ((*result)[i].col, expected[i].col);
        EXPECT_FLOAT_EQ((*result)[i].value, expected[i].value);
    }
}

TEST(STIFFNESS, CONDUCTIVITY) {
    using Node  = Node<Millimeter>;
    using Nodes = Nodes<Millimeter>;

    Triangle triangle{0, 1, 2};
    Nodes nodes = {
        Node{   0,    0,    0},
        Node{1000,    0,    0},
        Node{   0, 1000,    0}
    };

    std::vector<Triplets<float>> experiments;
    for (float i = 1.0f; i <= 3.0f; i++) {
        std::optional<Triplets<float>> experiment = paulista::stiffness::triangle::local(triangle, nodes, i);
        ASSERT_TRUE(experiment);

        experiments.push_back(*experiment);
    }

    Triplets<float> reference = experiments.front();
    for (std::size_t i = 0; i < 3; i++) {
        const Triplets<float>& current = experiments[i];
        for (std::size_t j = 0; j < 9; j++) {
            EXPECT_EQ(current[j].row, reference[j].row);
            EXPECT_EQ(current[j].row, reference[j].row);
            EXPECT_FLOAT_EQ(current[j].value, static_cast<float>(i + 1) * reference[j].value);
        }
    }
}

int
main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
