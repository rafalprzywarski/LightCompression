#include <gtest/gtest.h>
#include <Lens.hpp>
#include "RayHelpers.hpp"

namespace lc
{

struct LensTest : testing::Test
{
    Float Z_DISTANCE = 10;
    Float FOCAL_LENGTH = 3;
    Point ORIGIN{0, 0, 0};
    Point DIR_Z{0, 0, 1};
    ThinLens lens{Z_DISTANCE, FOCAL_LENGTH};
    Point FOCAL_POINT{0, 0, Z_DISTANCE + FOCAL_LENGTH};
    Float EPS = 1e-5f;
};

TEST_F(LensTest, central_ray_should_pass_through)
{
    Ray central{Ray{ORIGIN, DIR_Z}};
    auto refracted = lens.refract(central);
    ASSERT_THAT(refracted, RayPassesThrough(FOCAL_POINT, EPS));
    ASSERT_THAT(central, RayPassesThrough(refracted.getOrigin(), EPS));
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

}
