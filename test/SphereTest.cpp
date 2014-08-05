#include <gtest/gtest.h>
#include <Sphere.hpp>

namespace lc
{

TEST(SphereTest, should_intersect_with_rays)
{
    EXPECT_TRUE((Sphere{{5, 0, 0}, 1}.intersects(Ray{{5, 0, 10}, {0, 0, -1}}))) << "hit";
    EXPECT_FALSE((Sphere{{5, 0, 0}, 1}.intersects(Ray{{5, 1.005, 10}, {0, 0, -1}}))) << "miss";
    EXPECT_FALSE((Sphere{{5, 0, 0}, 1}.intersects(Ray{{5, 0, 1.05}, {0, 0, 1}}))) << "negative distance";
    EXPECT_TRUE((Sphere{{5, 0, 0}, 1}.intersects(Ray{{5, 0, 10}, {0, 0, -10}}))) << "hit, not normalized distance";
}

}
