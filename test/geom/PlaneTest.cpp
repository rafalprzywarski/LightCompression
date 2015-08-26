#include <gtest/gtest.h>
#include <geom/Plane.hpp>
#include "RayHelpers.hpp"

namespace lc
{
namespace geom
{

struct PlaneTest : testing::Test
{
    Float EPS = 1e-5;
};

TEST_F(PlaneTest, should_provide_ray_distance_when_ray_hits_front_side)
{
    EXPECT_NEAR(*Plane({-1, 0, 0}, -7).getDistance(Ray{{1, 2, 4}, {1, 0, 0}}), 6, EPS);
    EXPECT_NEAR(*Plane({0, -1, 0}, -7).getDistance(Ray{{1, 2, 4}, {0, 1, 0}}), 5, EPS);
    EXPECT_NEAR(*Plane({0, 0, -1}, -7).getDistance(Ray{{1, 2, 4}, {0, 0, 1}}), 3, EPS);
}

TEST_F(PlaneTest, should_not_provide_ray_distance_when_ray_hits_back_side)
{
    EXPECT_FALSE(Plane({1, -1, 1}, 10).getDistance(Ray{{-1, 0, 0}, {1, 0, 0}}));
}

TEST_F(PlaneTest, should_not_provide_ray_distance_when_ray_is_parallel)
{
    EXPECT_FALSE(Plane({1, 0, 0}, 10).getDistance(Ray{{0, 0, 0}, {0, 1, 0}}));
}

TEST_F(PlaneTest, should_not_provide_ray_distance_when_ray_does_not_hit)
{
    EXPECT_FALSE(Plane({1, 0, 0}, 1).getDistance(Ray{{1, 0, 0}, {-1, 0, 0}})) << "origin on the plane";
    EXPECT_FALSE(Plane({1, 0, 0}, 1).getDistance(Ray{{-1, 0, 0}, {-1, 0, 0}})) << "origin in front of the plane";
}

}
}
