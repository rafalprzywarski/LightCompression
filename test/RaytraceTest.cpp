#include <gtest/gtest.h>
#include <scene/Scene.hpp>
#include <scene/Sphere.hpp>
#include <Camera.hpp>
#include <Lens.hpp>
#include <Distribution.hpp>

namespace lc
{

struct RaytraceTest : testing::Test
{
    DirectRayOnly directRayOnly;
};

TEST_F(RaytraceTest, should_trace_all_lights)
{
    auto sensor = createCameraSensor({16, 8}, 1, directRayOnly);
    ThinLens lens{0, 1000};
    auto camera = createCamera(sensor, lens);
    scene::Lights lights{{{{0, 0, 100}, 3}}, {{{6, 3, 200}, 4}}};
    auto img = scene::createScene(scene::Spheres<void>{}, lights).raytraceImage(camera);
    auto v = view(img);
    EXPECT_EQ(0u, v(0, 0)) << "background";
    EXPECT_EQ(0u, v(8, 0)) << "background";
    EXPECT_EQ(0u, v(4, 4)) << "background";
    EXPECT_EQ(255u, v(8, 4)) << "first sphere";
    EXPECT_EQ(255u, v(7, 3)) << "first sphere";
    EXPECT_EQ(255u, v(14, 7)) << "second sphere";
}

TEST_F(RaytraceTest, should_trace_using_lens)
{
    auto sensor = createCameraSensor({8, 8}, 1, directRayOnly);
    Float FOCAL_LENGTH = Float{8} / 3;
    ThinLens lens{0, FOCAL_LENGTH};
    auto camera = createCamera(sensor, lens);
    scene::Lights lights{{{{0, 0, FOCAL_LENGTH + 5}, 3}}};
    auto img = createScene(scene::Spheres<void>{}, lights).raytraceImage(camera);
    auto v = view(img);
    EXPECT_EQ(255u, v(4, 4));
    EXPECT_EQ(255u, v(4, 5));
    EXPECT_EQ(0u, v(4, 6));
    EXPECT_EQ(0u, v(4, 7));
}

TEST_F(RaytraceTest, should_trace_reflective_spheres)
{
    auto sensor = createCameraSensor({3, 1}, 1, directRayOnly);
    ThinLens lens{0, 100000};
    auto camera = createCamera(sensor, lens);
    scene::Light light{{{5, 0, 3}, 1}};
    scene::Sphere<void> sphere{{{-1, 0, 4}, std::sqrt(Float(2))}};
    auto img = scene::createScene(scene::Spheres<void>{sphere}, {light}).raytraceImage(camera);
    auto v = view(img);
    EXPECT_EQ(0u, v(2, 0)) << "sphere missed";
    EXPECT_EQ(255u, v(1, 0)) << "reflected light";
    EXPECT_EQ(0u, v(0, 0)) << "no reflection of light";
}


}
