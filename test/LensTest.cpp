#include <gtest/gtest.h>
#include <Lens.hpp>
#include "RayHelpers.hpp"

namespace lc
{

struct LensTest : testing::Test
{
    Float Z_DISTANCE = 10;
    Float INV_R1 = 3;
    Float INV_R2 = 4;
    Point ORIGIN{0, 0, 0};
    Point DIR_Z{0, 0, 1};
};

TEST_F(LensTest, central_ray_should_pass_through)
{
    Ray central{Ray{ORIGIN, DIR_Z}};
    ThinLens lens{Z_DISTANCE, INV_R1, INV_R2};

    ASSERT_THAT(lens.refract(central), RayEq(central));
}

}
