#include <gtest/gtest.h>
#include <paulista/paulista.hpp>

TEST(TRIPLETS, CONVERSION) {
    paulista::stiffness::Triplets<double> triplets = {
        {0, 0, 1.0},
        {0, 1, 2.0},
        {1, 0, 2.0},
        {1, 1, 3.0}
    };

    paulista::sparse::Matrix<double> matrix(triplets, 2, 2);

    EXPECT_EQ(matrix.rows, 2);
    EXPECT_EQ(matrix.cols, 2);
    EXPECT_EQ( matrix.nnz, 4);

    EXPECT_EQ(matrix.pointers.size(), 3);
    EXPECT_EQ( matrix.indices.size(), 4);
    EXPECT_EQ(  matrix.values.size(), 4);

    EXPECT_EQ(matrix.pointers[0], 0);
    EXPECT_EQ(matrix.pointers[1], 2);
    EXPECT_EQ(matrix.pointers[2], 4);
}

TEST(TRIPLETS, EXPANSION) {
    paulista::stiffness::Triplets<double> triplets = {
          {0, 1, 5.0}
    };
    paulista::sparse::Matrix<double> matrix(triplets, 2, 2);

    ASSERT_EQ(matrix.nnz, 2);
    EXPECT_FLOAT_EQ(matrix.values[0], 5.0);
    EXPECT_FLOAT_EQ(matrix.values[1], 5.0);
}

TEST(TRIPLETS, ACCUMULATE) {
    using namespace paulista;

    stiffness::Triplets<double> triplets = {
          {0, 0, 1.0}
        , {0, 0, 2.0}
        , {0, 0, 3.0}
    };
    sparse::Matrix<double> matrix(triplets, 1, 1);

    EXPECT_EQ(matrix.nnz, 1);
    EXPECT_FLOAT_EQ(matrix.values[0], 6.0);
}

TEST(NONZERO, EMPTY) {
    paulista::Graph graph{{}};
    EXPECT_FALSE(paulista::sparse::nonzero(graph));
}

TEST(NONZERO, K4) {
    paulista::Graph graph{{
        {1, 2, 3},  // vertex 0 connected to 1, 2, 3
        {0, 2, 3},  // vertex 1 connected to 0, 2, 3
        {0, 1, 3},  // vertex 2 connected to 0, 1, 3
        {0, 1, 2}   // vertex 3 connected to 0, 1, 2
    }};

    std::optional<std::size_t> result = paulista::sparse::nonzero(graph);
    ASSERT_TRUE(result);
    EXPECT_EQ(*result, 16); // 4 vertices * 3 connections each + 4 self connection = 16 non-zeros
}

TEST(NONZERO, Q10) {
    paulista::Graph graph{{
          {1, 9}
        , {2, 0}
        , {3, 1}
        , {4, 2}
        , {5, 3}
        , {6, 4}
        , {7, 5}
        , {8, 6}
        , {9, 7}
        , {8, 0}
    }};

    std::optional<std::size_t> result = paulista::sparse::nonzero(graph);
    ASSERT_TRUE(result);
    EXPECT_EQ(*result, 30); // 10 vertices * 2 connections each + 10 self connections = 30 non-zeros
}

TEST(NONZERO, TRIANGLES) {
    using paulista::element::Triangle;
    using paulista::Elements;

    Elements elements = {
          Triangle{0, 1, 4}
        , Triangle{1, 2, 4}
        , Triangle{2, 3, 4}
        , Triangle{3, 4, 0}
    };

    std::optional<paulista::Graph> graph = paulista::graph::node::dual(elements);
    ASSERT_TRUE(graph);

    std::optional<std::size_t> result = paulista::sparse::nonzero(*graph);
    ASSERT_TRUE(result);
    // Expected adjacencies: {1,3,4}, {0,2,4}, {1,3,4}, {0,2,4}, {0,1,2,3}
    EXPECT_EQ(*result, 21); // 3+3+3+3+4+5= 20 non-zeros
}

TEST(MAPPING, K2) {
    // Simple 2x2 fully connected graph
    paulista::Graph graph{{
        {1},    // node 0 connected to node 1
        {0}     // node 1 connected to node 0
    }};

    paulista::sparse::coordinate::Map mapping = paulista::sparse::coordinate::mapping(graph);

    ASSERT_TRUE(mapping.contains({0, 0}));
    ASSERT_TRUE(mapping.contains({0, 1}));
    ASSERT_TRUE(mapping.contains({1, 0}));
    ASSERT_TRUE(mapping.contains({1, 1}));
}

TEST(MAPPING, K3) {
    paulista::Graph graph{{
        {1, 2},     // node 0 connected to 1, 2
        {0, 2},     // node 1 connected to 0, 2
        {0, 1}      // node 2 connected to 0, 1
    }};

    paulista::sparse::coordinate::Map mapping = paulista::sparse::coordinate::mapping(graph);

    ASSERT_TRUE(mapping.contains({0, 0}));
    ASSERT_TRUE(mapping.contains({0, 1}));
    ASSERT_TRUE(mapping.contains({0, 2}));

    ASSERT_TRUE(mapping.contains({1, 0}));
    ASSERT_TRUE(mapping.contains({1, 1}));
    ASSERT_TRUE(mapping.contains({1, 2}));

    ASSERT_TRUE(mapping.contains({2, 0}));
    ASSERT_TRUE(mapping.contains({2, 1}));
    ASSERT_TRUE(mapping.contains({2, 2}));
}

TEST(MAPPING, Q10) {
    paulista::Graph graph{{
          {1, 9}
        , {2, 0}
        , {3, 1}
        , {4, 2}
        , {5, 3}
        , {6, 4}
        , {7, 5}
        , {8, 6}
        , {9, 7}
        , {8, 0}
    }};

    paulista::sparse::coordinate::Map mapping = paulista::sparse::coordinate::mapping(graph);

    std::size_t nonzero = 0;
    for (std::size_t i = 0; i < 10; i++) {
        std::size_t j = (i + 1) % 10;
        std::size_t k = (i + 9) % 10;

        std::vector<std::size_t> vs{i, j, k};
        std::sort(vs.begin(), vs.end());

        ASSERT_TRUE(mapping.contains({i, vs[0]}));
        ASSERT_TRUE(mapping.contains({i, vs[1]}));
        ASSERT_TRUE(mapping.contains({i, vs[2]}));

        EXPECT_EQ(mapping.at({vs[0], i}), nonzero++);
        EXPECT_EQ(mapping.at({vs[1], i}), nonzero++);
        EXPECT_EQ(mapping.at({vs[2], i}), nonzero++);
    }
}

int
main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

