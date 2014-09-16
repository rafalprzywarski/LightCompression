#include <gtest/gtest.h>
#include <geom/Sphere.hpp>
#include "RayHelpers.hpp"

namespace lc
{
namespace geom
{

struct SphereTest : testing::Test
{
    Float EPS = 1e-5;
};

TEST_F(SphereTest, should_intersect_with_rays)
{
    EXPECT_TRUE((Sphere{{5, 0, 0}, 1}.intersects(Ray{{5, 0, 10}, {0, 0, -1}}))) << "hit";
    EXPECT_FALSE((Sphere{{5, 0, 0}, 1}.intersects(Ray{{5, 1.005, 10}, {0, 0, -1}}))) << "miss";
    EXPECT_FALSE((Sphere{{5, 0, 0}, 1}.intersects(Ray{{5, 0, 1.05}, {0, 0, 1}}))) << "negative distance";
    EXPECT_TRUE((Sphere{{5, 0, 0}, 1}.intersects(Ray{{5, 0, 10}, {0, 0, -10}}))) << "hit, not normalized distance";
}

TEST_F(SphereTest, should_provide_surface_normal_when_ray_hits)
{
    Sphere sphere{{-1, -2, 3}, 5};
    auto normal = *sphere.getSurfaceNormalRay(Ray{{-10, 1, 3}, {1, 0, 0}});
    EXPECT_THAT(normal, RayHasOrigin(Point{-5, 1, 3}, EPS));
    EXPECT_THAT(normal, RayHasDirection(Vector{Float(-4)/5, Float(3)/5, 0}, EPS));
}

TEST_F(SphereTest, should_not_provide_surface_normal_when_ray_does_not_hit)
{
    EXPECT_FALSE((Sphere{{5, 0, 0}, 1}.getSurfaceNormalRay(Ray{{5, 1.005, 10}, {0, 0, -1}}))) << "miss";
    EXPECT_FALSE((Sphere{{5, 0, 0}, 1}.getSurfaceNormalRay(Ray{{5, 0, 1.05}, {0, 0, 1}}))) << "negative distance";
}

}
}
