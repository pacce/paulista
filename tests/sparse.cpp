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
    EXPECT_EQ(*result, 12); // 4 vertices * 3 connections each = 12 non-zeros
}

TEST(NONZERO, Q10) {
    paulista::Graph graph{{
        {1, 9},     // vertex 0 connected to 1, 9
        {0, 2},     // vertex 1 connected to 0, 2
        {1, 3},     // vertex 2 connected to 1, 3
        {2, 4},     // vertex 3 connected to 2, 4
        {3, 5},     // vertex 4 connected to 3, 5
        {4, 6},     // vertex 5 connected to 4, 6
        {5, 7},     // vertex 6 connected to 5, 7
        {6, 8},     // vertex 7 connected to 6, 8
        {7, 9},     // vertex 8 connected to 7, 9
        {8, 0}      // vertex 9 connected to 8, 0
    }};

    std::optional<std::size_t> result = paulista::sparse::nonzero(graph);
    ASSERT_TRUE(result);
    EXPECT_EQ(*result, 20); // 10 vertices * 2 connections each = 20 non-zeros
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
    EXPECT_EQ(*result, 16); // 3+3+3+3+4 = 16 non-zeros
}

int 
main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

