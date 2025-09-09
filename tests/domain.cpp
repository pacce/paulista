#include <gtest/gtest.h>
#include <paulista/paulista.hpp>

using paulista::domain::Element;
using paulista::domain::element::Triangle;
using paulista::domain::element::Tetrahedron;
using paulista::domain::element::is_triangle;
using paulista::domain::element::is_tetrahedron;

TEST(VISITOR, TRIANGLE) {
    Element triangle    = Triangle{0, 1, 2};
    Element tetrahedron = Tetrahedron{0, 1, 2, 3};
    
    EXPECT_TRUE (std::visit(is_triangle, triangle));
    EXPECT_FALSE(std::visit(is_triangle, tetrahedron));
}

TEST(VISITOR, TETRAHEDRON) {
    Element triangle    = Triangle{0, 1, 2};
    Element tetrahedron = Tetrahedron{0, 1, 2, 3};
    
    EXPECT_FALSE(std::visit(is_tetrahedron, triangle));
    EXPECT_TRUE (std::visit(is_tetrahedron, tetrahedron));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
