#include <gtest/gtest.h>
#include <Raytrace.hpp>

namespace lc
{

TEST(RaytraceTest, should_trace_all_spheres)
{
    CameraSensor sensor{{16, 8}};
    Spheres spheres{{{8, 4, 100}, 3}, {{14, 7, 200}, 4}};
    auto img = raytrace(sensor, spheres, {});
    auto v = view(img);
    EXPECT_EQ(0u, v(0, 0)) << "background";
    EXPECT_EQ(0u, v(8, 0)) << "background";
    EXPECT_EQ(0u, v(4, 4)) << "background";
    EXPECT_EQ(255u, v(8, 4)) << "first sphere";
    EXPECT_EQ(255u, v(7, 3)) << "first sphere";
    EXPECT_EQ(255u, v(14, 7)) << "second sphere";
}

}
