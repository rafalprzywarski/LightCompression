#include <gtest/gtest.h>
#include <scene/Scene.hpp>
#include <scene/Sphere.hpp>
#include <scene/Material.hpp>
#include <Camera.hpp>
#include <geom/Lens.hpp>
#include <Distribution.hpp>

namespace lc
{
namespace scene
{

struct RaytraceTest : testing::Test
{
    using Spheres = Spheres<MirrorMaterial>;
    DirectRayOnly directRayOnly;
    MirrorMaterial mirror;
};

TEST_F(RaytraceTest, should_trace_all_lights)
{
    auto sensor = createCameraSensor({16, 8}, 1, directRayOnly);
    geom::ThinLens lens{0, 1000};
    auto camera = createCamera(sensor, lens);
    Lights lights{{{{0, 0, 100}, 3}}, {{{6, 3, 200}, 4}}};
    auto img = createScene(Spheres{}, lights).raytraceImage(camera);
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
    geom::ThinLens lens{0, FOCAL_LENGTH};
    auto camera = createCamera(sensor, lens);
    Lights lights{{{{0, 0, FOCAL_LENGTH + 5}, 3}}};
    auto img = createScene(Spheres{}, lights).raytraceImage(camera);
    auto v = view(img);
    EXPECT_EQ(255u, v(4, 4));
    EXPECT_EQ(255u, v(4, 5));
    EXPECT_EQ(0u, v(4, 6));
    EXPECT_EQ(0u, v(4, 7));
}

TEST_F(RaytraceTest, should_trace_reflective_spheres)
{
    auto sensor = createCameraSensor({3, 1}, 1, directRayOnly);
    geom::ThinLens lens{0, 100000};
    auto camera = createCamera(sensor, lens);
    Light light{{{5, 0, 3}, 1}};
    Sphere<MirrorMaterial> sphere{{{-1, 0, 4}, std::sqrt(Float(2))}, mirror};
    auto img = createScene(Spheres{sphere}, {light}).raytraceImage(camera);
    auto v = view(img);
    EXPECT_EQ(0u, v(2, 0)) << "sphere missed";
    EXPECT_EQ(255u, v(1, 0)) << "reflected light";
    EXPECT_EQ(0u, v(0, 0)) << "no reflection of light";
}


}
}
