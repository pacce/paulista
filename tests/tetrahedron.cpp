#include <gtest/gtest.h>
#include <paulista/paulista.hpp>

using paulista::Element;
using paulista::element::Tetrahedron;
using paulista::element::is_triangle;
using paulista::element::is_tetrahedron;

using paulista::domain::Centroid;
using paulista::domain::Node;
using paulista::domain::Nodes;

using paulista::geometry::dimension::Meter;
using paulista::geometry::dimension::Millimeter;

using paulista::stiffness::Triplets;

TEST(VOLUME, SIMPLE) {
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

TEST(VOLUME, REGULAR) {
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

TEST(VOLUME, BOUNDS) {
    using Node      = Node<Meter>;

    Nodes<Meter> nodes = {
        Node(0, 0, 0),
        Node(1, 1, 1)
    };
    Tetrahedron tetrahedron{0, 1, 2, 3};

    EXPECT_FALSE(tetrahedron.volume(nodes));
}

TEST(CENTROID, SIMPLE) {
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

TEST(CENTROID, REGULAR) {
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

TEST(CENTROID, BOUNDS) {
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

TEST(VISITOR, TRIANGLE) {
    Element tetrahedron = Tetrahedron{0, 1, 2, 3};
    EXPECT_FALSE(std::visit(is_triangle, tetrahedron));
}

TEST(VISITOR, TETRAHEDRON) {
    Element tetrahedron = Tetrahedron{0, 1, 2, 3};
    EXPECT_TRUE (std::visit(is_tetrahedron, tetrahedron));
}

TEST(TETRAHEDRON, EMPTY) {
    Tetrahedron tetrahedron{0, 1, 2, 3};
    Nodes<Meter> nodes;

    EXPECT_FALSE(paulista::stiffness::tetrahedron::local(tetrahedron, nodes, 1.0f));
}

TEST(TETRAHEDRON, INDICES) {
    using Node  = Node<Meter>;
    using Nodes = Nodes<Meter>;

    Tetrahedron tetrahedron{0, 1, 2, 5};
    Nodes nodes = {
        Node{0, 0, 0},
        Node{1, 0, 0},
        Node{0, 1, 0},
        Node{0, 0, 1}
    };

    EXPECT_FALSE(paulista::stiffness::tetrahedron::local(tetrahedron, nodes, 1.0f));
}

TEST(TETRAHEDRON, UNIT) {
    using Node  = Node<Millimeter>;
    using Nodes = Nodes<Millimeter>;

    Tetrahedron tetrahedron{0, 1, 2, 3};
    Nodes nodes = {
        Node{   0,    0,    0},
        Node{1000,    0,    0},
        Node{   0, 1000,    0},
        Node{   0,    0, 1000}
    };

    std::optional<Triplets<float>> result = paulista::stiffness::tetrahedron::local(tetrahedron, nodes, 1.0f);
    ASSERT_TRUE(result);
    EXPECT_EQ(result->size(), 16);

    for (std::size_t i = 0; i < 16; i++) {
        EXPECT_GE((*result)[i].row, 0);
        EXPECT_LE((*result)[i].row, 3);
        EXPECT_GE((*result)[i].col, 0);
        EXPECT_LE((*result)[i].col, 3);
    }
}

TEST(TETRAHEDRON, CONDUCTIVITY) {
    using Node  = Node<Millimeter>;
    using Nodes = Nodes<Millimeter>;

    Tetrahedron tetrahedron{0, 1, 2, 3};
    Nodes nodes = {
        Node{   0,    0,    0},
        Node{1000,    0,    0},
        Node{   0, 1000,    0},
        Node{   0,    0, 1000}
    };

    std::vector<Triplets<float>> experiments;
    for (float i = 1.0f; i <= 3.0f; i++) {
        std::optional<Triplets<float>> experiment = paulista::stiffness::tetrahedron::local(tetrahedron, nodes, i);
        ASSERT_TRUE(experiment);

        experiments.push_back(*experiment);
    }

    Triplets<float> reference = experiments.front();
    for (std::size_t i = 0; i < 3; i++) {
        const Triplets<float>& current = experiments[i];
        for (std::size_t j = 0; j < 16; j++) {
            EXPECT_EQ(current[j].row, reference[j].row);
            EXPECT_EQ(current[j].col, reference[j].col);
            EXPECT_FLOAT_EQ(current[j].value, static_cast<float>(i + 1) * reference[j].value);
        }
    }
}

int
main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
