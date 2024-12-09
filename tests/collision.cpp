#include <gtest/gtest.h>
#include <paulista/paulista.hpp>
#include <rapidcheck/gtest.h>

TEST(SUPPORT, EMPTY) {
    paulista::collision::Shape      ps;
    paulista::tridimensional::Point x(1, 0, 0);

    ASSERT_FALSE(paulista::collision::support(ps, x));
}

TEST(SUPPORT, INCREASING) {
    paulista::collision::Shape ps;
    for (std::size_t i = 0; i < 100; i++) {
        ps.emplace_back(i, i, i);
    }

    paulista::tridimensional::Point x(1, 0, 0);
    paulista::tridimensional::Point y(0, 1, 0);
    paulista::tridimensional::Point z(0, 0, 1);

    std::optional<paulista::tridimensional::Point> p = std::nullopt;

    p = paulista::collision::support(ps, x);
    ASSERT_TRUE(p);
    EXPECT_EQ(p, ps.back());

    p = paulista::collision::support(ps, y);
    ASSERT_TRUE(p);
    EXPECT_EQ(p, ps.back());

    p = paulista::collision::support(ps, z);
    ASSERT_TRUE(p);
    EXPECT_EQ(p, ps.back());
}

TEST(COLLISION, EMPTY) {
    paulista::collision::Shape xs;
    paulista::collision::Shape ys;

    ASSERT_FALSE(paulista::collision::detect(xs, ys));
}

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
