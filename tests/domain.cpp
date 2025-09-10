#include <gtest/gtest.h>
#include <paulista/paulista.hpp>

using paulista::domain::Element;
using paulista::domain::Elements;
using paulista::domain::element::Triangle;
using paulista::domain::element::Tetrahedron;
using paulista::domain::element::is_triangle;
using paulista::domain::element::is_tetrahedron;
using paulista::domain::Centroid;
using paulista::domain::Node;
using paulista::domain::Nodes;
using paulista::geometry::dimension::Meter;
using paulista::geometry::tridimensional::Point;

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

TEST(CENTROID, TRIANGLE) {
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

TEST(CENTROID, TRIANGLE_BOUNDS) {
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

TEST(CENTROID, TETRAHEDRON) {
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

TEST(CENTROID, TETRAHEDRON_REGULAR) {
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

TEST(CENTROID, TETRAHEDRON_BOUNDS) {
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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
