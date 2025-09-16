#include <gtest/gtest.h>
#include <paulista/paulista-sparse.hpp>
#include <paulista/paulista-stiffness.hpp>

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

int 
main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

