#include <gtest/gtest.h>
#include <paulista/paulista.hpp>

using paulista::element::Triangle;
using paulista::element::Tetrahedron;
using paulista::Elements;
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

TEST(DUAL, MIXED) {
    struct Experiment {
        std::vector<node::Indices>  adjacencies;
        paulista::graph::Common     common;
    };

    Elements elements = {
          Tetrahedron{0, 1, 3, 4}   // 0
        , Tetrahedron{1, 2, 3, 6}   // 1
        , Tetrahedron{3, 4, 6, 7}   // 2
        , Tetrahedron{1, 4, 5, 6}   // 3
        , Tetrahedron{1, 3, 4, 6}   // 4
        , Triangle{0, 4, 1}         // 5
        , Triangle{1, 4, 5}         // 6
    };
    std::optional<Nodal> nodal = paulista::graph::nodal(8, elements);
    ASSERT_TRUE(nodal);

    std::vector<Experiment> experiments = {
        {
               {
                     {1, 2, 3, 4, 5, 6}
                   , {0, 2, 3, 4, 5, 6}
                   , {0, 1, 3, 4, 5, 6}
                   , {0, 1, 2, 4, 5, 6}
                   , {0, 1, 2, 3, 5, 6}
                   , {0, 1, 2, 3, 4, 6}
                   , {0, 1, 2, 3, 4, 5}
               }
             , paulista::graph::common::Point{}
        }
        , {
               {
                     {1, 2, 3, 4, 5, 6}
                   , {0, 2, 3, 4}
                   , {0, 1, 3, 4}
                   , {0, 1, 2, 4, 5, 6}
                   , {0, 1, 2, 3, 5, 6}
                   , {0, 3, 4, 6}
                   , {0, 3, 4, 5}
               }
             , paulista::graph::common::Edge{}
        }
        , {
               {
                     {4, 5}
                   , {4}
                   , {4}
                   , {4, 6}
                   , {0, 1, 2, 3}
                   , {0}
                   , {3}
               }
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

TEST(DEGREE, COMPARISON) {
    Degree xs{0, 2};
    Degree ys{1, 3};
    Degree zs{2, 2};

    EXPECT_TRUE(xs < ys);
    EXPECT_FALSE(ys < xs);
    EXPECT_FALSE(xs < zs);

    EXPECT_TRUE(xs <= ys);
    EXPECT_TRUE(xs <= zs);
    EXPECT_FALSE(ys <= xs);

    EXPECT_FALSE(xs > ys);
    EXPECT_TRUE(ys > xs);
    EXPECT_FALSE(xs > zs);

    EXPECT_FALSE(xs >= ys);
    EXPECT_TRUE(xs >= zs);
    EXPECT_TRUE(ys >= xs);

    EXPECT_FALSE(xs == ys);
    EXPECT_TRUE(xs == zs);

    EXPECT_TRUE(xs != ys);
    EXPECT_FALSE(xs != zs);
}

TEST(DEGREES, K4) {
    Dual dual = {{
        {1, 2, 3},  // vertex 0 connected to 1, 2, 3
        {0, 2, 3},  // vertex 1 connected to 0, 2, 3
        {0, 1, 3},  // vertex 2 connected to 0, 1, 3
        {0, 1, 2}   // vertex 3 connected to 0, 1, 2
    }};

    std::optional<std::list<Degree>> result = paulista::graph::degrees(dual);
    ASSERT_TRUE(result);
    ASSERT_EQ(result->size(), 4);

    // All vertices in K4 have degree 3
    for (const Degree& degree : *result) {
        EXPECT_EQ(degree.value, 3);
    }
}

TEST(DEGREES, Q10) {
    Dual dual = {{
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

    std::optional<std::list<Degree>> result = paulista::graph::degrees(dual);
    ASSERT_TRUE(result);
    ASSERT_EQ(result->size(), 10);

    // All vertices in Q10 (cycle of 10) have degree 2
    for (const Degree& degree : *result) {
        EXPECT_EQ(degree.value, 2);
    }
}

TEST(ORDERING, K4) {
    Dual dual = {{
        {1, 2, 3},  // vertex 0 connected to 1, 2, 3
        {0, 2, 3},  // vertex 1 connected to 0, 2, 3
        {0, 1, 3},  // vertex 2 connected to 0, 1, 3
        {0, 1, 2}   // vertex 3 connected to 0, 1, 2
    }};

    std::optional<std::list<Degree>> degrees = paulista::graph::degrees(dual);
    ASSERT_TRUE(degrees);

    std::optional<std::vector<Ordering>> result = paulista::graph::ordering(dual, *degrees);
    ASSERT_TRUE(result);
    ASSERT_EQ(result->size(), 4);

    // For K4, all orderings are valid (all vertices have same degree initially)
    std::set<std::size_t> vertices(result->begin(), result->end());
    EXPECT_EQ(vertices.size(), 4);
    for (std::size_t i = 0; i < 4; i++) {
        EXPECT_TRUE(vertices.contains(i));
    }
}

TEST(ORDERING, Q10) {
    Dual dual = {{
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

    std::optional<std::list<Degree>> degrees = paulista::graph::degrees(dual);
    ASSERT_TRUE(degrees);

    std::optional<std::vector<Ordering>> result = paulista::graph::ordering(dual, *degrees);
    ASSERT_TRUE(result);
    ASSERT_EQ(result->size(), 10);

    // For Q10, all vertices should be included in ordering
    std::set<std::size_t> vertices(result->begin(), result->end());
    EXPECT_EQ(vertices.size(), 10);
    for (std::size_t i = 0; i < 10; i++) {
        EXPECT_TRUE(vertices.contains(i));
    }
}

TEST(COLOR, EMPTY) {
    ASSERT_FALSE(paulista::graph::color({}));
}

TEST(COLOR, K4) {
    Dual dual = {{
        {1, 2, 3},  // vertex 0 connected to 1, 2, 3
        {0, 2, 3},  // vertex 1 connected to 0, 2, 3
        {0, 1, 3},  // vertex 2 connected to 0, 1, 3
        {0, 1, 2}   // vertex 3 connected to 0, 1, 2
    }};

    std::optional<std::vector<Color>> result = paulista::graph::color(dual);
    ASSERT_TRUE(result);

    // Verify proper coloring: no two adjacent vertices have same color
    for (std::size_t vertex = 0; vertex < 4; vertex++) {
        for (node::Index neighbor : dual.adjacencies[vertex]) {
            EXPECT_NE(result->at(vertex), result->at(neighbor));
        }
    }

    // K4 requires exactly 4 colors (chromatic number = 4)
    std::set<Color> unique(result->begin(), result->end());
    EXPECT_EQ(unique.size(), 4);
}

TEST(COLOR, Q10) {
    Dual dual = {{
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

    std::optional<std::vector<Color>> result = paulista::graph::color(dual);
    ASSERT_TRUE(result);

    // Verify proper coloring: no two adjacent vertices have same color
    for (std::size_t vertex = 0; vertex < 10; vertex++) {
        for (node::Index neighbor : dual.adjacencies[vertex]) {
            EXPECT_NE(result->at(vertex), result->at(neighbor));
        }
    }

    // Q10 (cycle of 10) requires exactly 2 colors (chromatic number = 2)
    std::set<Color> unique(result->begin(), result->end());
    EXPECT_EQ(unique.size(), 2);
}

int
main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
