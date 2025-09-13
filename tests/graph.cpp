#include <gtest/gtest.h>
#include <paulista/paulista.hpp>

using paulista::domain::element::Triangle;
using paulista::domain::element::Tetrahedron;
using paulista::domain::Elements;
using paulista::graph::Nodal;

TEST(NODAL, EMPTY) {
    Elements elements;
    EXPECT_FALSE(paulista::graph::nodal(5, elements));
}

TEST(NODAL, TRIANGLES) {
    Elements elements = {
          Triangle{0, 1, 4}
        , Triangle{1, 2, 4}
        , Triangle{2, 3, 4}
        , Triangle{3, 4, 0}
    };
    std::optional<Nodal> actual     = paulista::graph::nodal(5, elements);
    std::optional<Nodal> expected   = Nodal{{
          {0, 3}
        , {0, 1}
        , {1, 2}
        , {2, 3}
        , {0, 1, 2, 3}
    }};

    ASSERT_TRUE(actual);
    ASSERT_EQ(actual->indices.size(), expected->indices.size());
    for (std::size_t i = 0; i < expected->indices.size(); i++) {
        const std::vector<std::size_t>& xs = actual->indices[i];
        const std::vector<std::size_t>& ys = expected->indices[i];
        ASSERT_EQ(xs.size(), ys.size());

        for (std::size_t j = 0; j < ys.size(); j++) {
            EXPECT_EQ(xs[j], ys[j]);
        }
    }
}

TEST(NODAL, TETRAHEDRON) {
    Elements elements = {
          Tetrahedron{0, 1, 3, 4}
        , Tetrahedron{1, 2, 3, 6}
        , Tetrahedron{3, 4, 6, 7}
        , Tetrahedron{1, 4, 5, 6}
        , Tetrahedron{1, 3, 4, 6}
    };
    std::optional<Nodal> actual     = paulista::graph::nodal(8, elements);
    std::optional<Nodal> expected   = Nodal{{
          {0}
        , {0, 1, 3, 4}
        , {1}
        , {0, 1, 2, 4}
        , {0, 2, 3, 4}
        , {3}
        , {1, 2, 3, 4}
        , {2}
    }};

    ASSERT_TRUE(actual);
    ASSERT_EQ(actual->indices.size(), expected->indices.size());
    for (std::size_t i = 0; i < expected->indices.size(); i++) {
        const std::vector<std::size_t>& xs = actual->indices[i];
        const std::vector<std::size_t>& ys = expected->indices[i];
        ASSERT_EQ(xs.size(), ys.size());

        for (std::size_t j = 0; j < ys.size(); j++) {
            EXPECT_EQ(xs[j], ys[j]);
        }
    }
}

int
main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
