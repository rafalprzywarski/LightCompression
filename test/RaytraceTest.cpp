#include <gtest/gtest.h>
#include <Raytrace.hpp>
#include <Lens.hpp>

namespace lc
{

TEST(RaytraceTest, should_trace_all_spheres)
{
    CameraSensor sensor{{16, 8}, 1};
    ThinLens lens{0, 1000};
    auto camera = createCamera(sensor, lens);
    Spheres spheres{{{0, 0, 100}, 3}, {{6, 3, 200}, 4}};
    auto img = raytraceImage(camera, spheres, {});
    auto v = view(img);
    EXPECT_EQ(0u, v(0, 0)) << "background";
    EXPECT_EQ(0u, v(8, 0)) << "background";
    EXPECT_EQ(0u, v(4, 4)) << "background";
    EXPECT_EQ(255u, v(8, 4)) << "first sphere";
    EXPECT_EQ(255u, v(7, 3)) << "first sphere";
    EXPECT_EQ(255u, v(14, 7)) << "second sphere";
}

TEST(RaytraceTest, should_trace_using_lens)
{
    CameraSensor sensor{{8, 8}, 1};
    Float FOCAL_LENGTH = Float{8} / 3;
    ThinLens lens{0, FOCAL_LENGTH};
    auto camera = createCamera(sensor, lens);
    Spheres spheres{{{0, 0, FOCAL_LENGTH + 5}, 3}};
    auto img = raytraceImage(camera, spheres, {});
    auto v = view(img);
    EXPECT_EQ(255u, v(4, 4));
    EXPECT_EQ(255u, v(4, 5));
    EXPECT_EQ(0u, v(4, 6));
    EXPECT_EQ(0u, v(4, 7));
}


}
