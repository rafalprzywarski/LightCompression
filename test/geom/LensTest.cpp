#include <gtest/gtest.h>
#include <geom/Lens.hpp>
#include "RayHelpers.hpp"

namespace lc
{
namespace geom
{

struct LensTest : testing::Test
{
    Float Z_DISTANCE = 10;
    Float FOCAL_LENGTH = 3;
    Point DIR_Z{0, 0, 1};
    ThinLens lens{Z_DISTANCE, FOCAL_LENGTH};
    Point FOCAL_POINT{0, 0, Z_DISTANCE + FOCAL_LENGTH};
    Float EPS = 1e-5f;

    auto rayFromTo(Point from, Point to) const
    {
        return Ray{from, to - from};
    }
};

TEST_F(LensTest, central_ray_should_pass_through)
{
    Ray central{{0, 0, 0}, DIR_Z};
    auto refracted = lens.refract(central);
    ASSERT_THAT(refracted, RayPassesThrough(FOCAL_POINT, EPS));
    ASSERT_THAT(central, RayPassesThrough(refracted.getOrigin(), EPS));
}

TEST_F(LensTest, ray_passing_thru_the_center_at_an_angle_should_pass_through)
{
    Vector ORIGIN{-3, 2, 0};
    Vector DEST{-ORIGIN[0], -ORIGIN[1], Z_DISTANCE * 2};
    auto central = rayFromTo(ORIGIN, DEST);
    auto refracted = lens.refract(central);
    EXPECT_THAT(refracted, RayPassesThrough(DEST, EPS));
    EXPECT_THAT(refracted, RayHasDirection(central.getDirection(), EPS));
    EXPECT_THAT(central, RayPassesThrough(refracted.getOrigin(), EPS));
}

TEST_F(LensTest, parallel_rays_should_pass_through_the_focal_point)
{
    Ray rays[]{Ray{{1, 2, 0}, DIR_Z}, Ray{{-3, 4, 1}, DIR_Z}, Ray{{4, 1, -3}, DIR_Z}};
    for (auto& ray : rays)
    {
        auto refracted = lens.refract(ray);
        EXPECT_THAT(refracted, RayPassesThrough(FOCAL_POINT, EPS));
        EXPECT_NEAR(ray.getOrigin()[0], refracted.getOrigin()[0], EPS);
        EXPECT_NEAR(ray.getOrigin()[1], refracted.getOrigin()[1], EPS);
        EXPECT_NEAR(Z_DISTANCE, refracted.getOrigin()[2], EPS);
    }
}

TEST_F(LensTest, rays_passing_though_the_focal_point_should_become_parallel)
{
    Point destinationPoints[]{
        {1, 2, Z_DISTANCE},
        {-3, 4, Z_DISTANCE},
        {4, 1, Z_DISTANCE}};
    for (auto& to : destinationPoints)
    {
        auto ray = rayFromTo(FOCAL_POINT, to);
        auto refracted = lens.refract(ray);
        EXPECT_THAT(refracted, RayHasDirection(-DIR_Z, EPS));
        EXPECT_NEAR(to[0], refracted.getOrigin()[0], EPS);
        EXPECT_NEAR(to[1], refracted.getOrigin()[1], EPS);
        EXPECT_NEAR(to[2], refracted.getOrigin()[2], EPS);
    }
}

}
}
