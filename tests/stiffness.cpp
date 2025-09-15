#include <gtest/gtest.h>
#include <paulista/paulista-stiffness.hpp>
#include <paulista/paulista-geometry.hpp>

using paulista::geometry::dimension::Meter;
using paulista::geometry::dimension::Millimeter;
using paulista::element::Triangle;
using paulista::domain::Node;
using paulista::domain::Nodes;
using paulista::stiffness::Triplets;

TEST(TRIANGLE, EMPTY) {
    Triangle triangle{0, 1, 2};
    Nodes<Meter> nodes;

    EXPECT_FALSE(paulista::stiffness::triangle::local(triangle, nodes, 1.0f));
}

TEST(TRIANGLE, INDICES) {
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

TEST(TRIANGLE, RIGHT) {
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

TEST(TRIANGLE, CONDUCTIVITY) {
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
