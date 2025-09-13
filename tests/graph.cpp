#include <gtest/gtest.h>
#include <paulista/paulista.hpp>

using paulista::domain::element::Triangle;
using paulista::domain::element::Tetrahedron;
using paulista::domain::Elements;
using paulista::graph::Nodal;
using paulista::graph::Dual;
using namespace paulista::graph;

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
        const node::Indices& xs = actual->indices[i];
        const node::Indices& ys = expected->indices[i];
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
        const node::Indices& xs = actual->indices[i];
        const node::Indices& ys = expected->indices[i];
        ASSERT_EQ(xs.size(), ys.size());

        for (std::size_t j = 0; j < ys.size(); j++) {
            EXPECT_EQ(xs[j], ys[j]);
        }
    }
}

TEST(DUAL, EMPTY) {
    Elements elements;
    Nodal nodal{{}};
    EXPECT_FALSE(paulista::graph::dual(nodal, elements, paulista::graph::common::Point{}));
    EXPECT_FALSE(paulista::graph::dual(nodal, elements, paulista::graph::common::Edge{}));
    EXPECT_FALSE(paulista::graph::dual(nodal, elements, paulista::graph::common::Face{}));
}

TEST(DUAL, TRIANGLES) {
    struct Experiment {
        std::vector<node::Indices>  adjacencies;
        paulista::graph::Common     common;
    };

    Elements elements = {
          Triangle{0, 1, 4}
        , Triangle{1, 2, 4}
        , Triangle{2, 3, 4}
        , Triangle{3, 4, 0}
    };
    std::optional<Nodal> nodal = paulista::graph::nodal(5, elements);
    ASSERT_TRUE(nodal);

    std::optional<Dual> actual = paulista::graph::dual(*nodal, elements, paulista::graph::common::Edge{});
    std::vector<Experiment> experiments = {
        {
               {{1, 2, 3}, {0, 2, 3}, {0, 1, 3}, {0, 1, 2}}
             , paulista::graph::common::Point{}
        }
        , {
               {{1, 3}, {0, 2}, {1, 3}, {0, 2}}
             , paulista::graph::common::Edge{}
        }
        , {
               {{}, {}, {}, {}}
             , paulista::graph::common::Face{}
        }
    };
    for (const Experiment& experiment : experiments) {
        std::optional<Dual> actual = paulista::graph::dual(*nodal, elements, experiment.common);

        ASSERT_TRUE(actual);
        ASSERT_EQ(actual->adjacencies.size(), experiment.adjacencies.size());
        for (std::size_t i = 0; i < experiment.adjacencies.size(); i++) {
            const node::Indices& xs = actual->adjacencies[i];
            const node::Indices& ys = experiment.adjacencies[i];
            ASSERT_EQ(xs.size(), ys.size());

            for (std::size_t j = 0; j < ys.size(); j++) {
                EXPECT_EQ(xs[j], ys[j]);
            }
        }
    }

}

TEST(DUAL, TETRAHEDRON) {
    struct Experiment {
        std::vector<node::Indices>  adjacencies;
        paulista::graph::Common     common;
    };

    Elements elements = {
          Tetrahedron{0, 1, 3, 4}
        , Tetrahedron{1, 2, 3, 6}
        , Tetrahedron{3, 4, 6, 7}
        , Tetrahedron{1, 4, 5, 6}
        , Tetrahedron{1, 3, 4, 6}
    };
    std::optional<Nodal> nodal = paulista::graph::nodal(8, elements);
    ASSERT_TRUE(nodal);

    std::vector<Experiment> experiments = {
        {
               {{1, 2, 3, 4}, {0, 2, 3, 4}, {0, 1, 3, 4}, {0, 1, 2, 4}, {0, 1, 2, 3}}
             , paulista::graph::common::Point{}
        }
        , {
               {{1, 2, 3, 4}, {0, 2, 3, 4}, {0, 1, 3, 4}, {0, 1, 2, 4}, {0, 1, 2, 3}}
             , paulista::graph::common::Edge{}
        }
        , {
               {{4}, {4}, {4}, {4}, {0, 1, 2, 3}}
             , paulista::graph::common::Face{}
        }
    };

    for (const Experiment& experiment : experiments) {
        std::optional<Dual> actual = paulista::graph::dual(*nodal, elements, experiment.common);

        ASSERT_TRUE(actual);
        ASSERT_EQ(actual->adjacencies.size(), experiment.adjacencies.size());
        for (std::size_t i = 0; i < experiment.adjacencies.size(); i++) {
            const node::Indices& xs = actual->adjacencies[i];
            const node::Indices& ys = experiment.adjacencies[i];
            ASSERT_EQ(xs.size(), ys.size());

            for (std::size_t j = 0; j < ys.size(); j++) {
                EXPECT_EQ(xs[j], ys[j]);
            }
        }
    }
}

int
main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
