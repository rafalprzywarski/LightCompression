#include <Lens.hpp>
#include <gmock/gmock.h>
#include "RayHelpers.hpp"

namespace lc
{

struct TwoElementCameraLensTest : testing::Test
{
    Float EPS = 1e-5f;
    Float SCALE = 2;
    Float FIRST_FOCAL_LENGTH = 5;
    Float SECOND_FOCAL_LENGTH = SCALE * FIRST_FOCAL_LENGTH;
    Ray INCOMING{{4, 5, 0}, {0, 0, 1}};
};

TEST_F(TwoElementCameraLensTest, should_rotate_and_scale_the_image)
{
    ThinLens FIRST_LENS{0, FIRST_FOCAL_LENGTH};
    ThinLens SECOND_LENS{FIRST_FOCAL_LENGTH + SECOND_FOCAL_LENGTH, SECOND_FOCAL_LENGTH};
    TwoElementCameraLens lens{FIRST_LENS, SECOND_LENS};
    
    auto refracted = lens.refract(INCOMING);
    ASSERT_THAT(refracted, RayPassesThrough(INCOMING.getOrigin() * -SCALE, EPS));
    ASSERT_THAT(refracted, RayHasDirection(INCOMING.getDirection(), EPS));
}

}
