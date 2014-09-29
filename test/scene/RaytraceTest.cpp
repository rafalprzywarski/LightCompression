#include <gtest/gtest.h>
#include <scene/Scene.hpp>
#include <scene/Sphere.hpp>
#include <scene/Material.hpp>
#include <Camera.hpp>
#include <geom/Lens.hpp>
#include <Distribution.hpp>
#include <deque>

namespace lc
{
namespace scene
{

struct RaytraceTest : testing::Test
{
    using Spheres = Spheres<MirrorMaterial>;
    DirectRayOnly directRayOnly;
    MirrorMaterial mirror;
    geom::NoLens noLens;

    template <typename Spheres>
    Float traceCentralRay(Spheres spheres, Light light)
    {
        auto sensor = createCameraSensor({1, 1}, 1, directRayOnly);
        auto camera = createCamera(sensor, noLens);
        auto img = createScene(spheres, {light}).raytraceImage(camera);
        return view(img)(0, 0);
    }
};

TEST_F(RaytraceTest, should_trace_all_lights)
{
    auto sensor = createCameraSensor({16, 8}, 1, directRayOnly);
    auto camera = createCamera(sensor, noLens);
    Lights lights{{{{0, 0, 100}, 3}, 255}, {{{6, 3, 200}, 4}, 255}};
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
    Lights lights{{{{0, 0, FOCAL_LENGTH + 5}, 3}, 255}};
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
    auto camera = createCamera(sensor, noLens);
    Light light{{{5, 0, 3}, 1}, 255};
    Sphere<MirrorMaterial> sphere{{{-1, 0, 4}, std::sqrt(Float(2))}, mirror};
    auto img = createScene(Spheres{sphere}, {light}).raytraceImage(camera);
    auto v = view(img);
    EXPECT_EQ(0u, v(2, 0)) << "sphere missed";
    EXPECT_EQ(255u, v(1, 0)) << "reflected light";
    EXPECT_EQ(0u, v(0, 0)) << "no reflection of light";
}

TEST_F(RaytraceTest, should_trace_brdf_materials)
{
    auto sensor = createCameraSensor({1, 1}, 1, RepeatedDirectRay{4096});
    auto camera = createCamera(sensor, noLens);
    Light light{{{0, 0, -40}, 20}, 255};
    using Material = BrdfMaterial<UniformDirections, ConstantBrdf>;
    Material material{{}, {1}};
    scene::Spheres<Material> spheres{{{{0, 0, 20}, 10}, material}};
    auto img = createScene(spheres, {light}).raytraceImage(camera);
    auto v = view(img);
    EXPECT_LT(v(0, 0), 30u) << "diffuse light";
    EXPECT_GT(v(0, 0), 20u) << "diffuse light";
}

TEST_F(RaytraceTest, should_trace_the_nearest_sphere)
{
    Light light{{{0, 0, 5}, 1}, 255};
    Spheres spheres{
        {{{0, 0, 2}, 1}, mirror},
        {{{0, 0, 8}, 1}, mirror},
        {{{0, 0, 11}, 1}, mirror},
        {{{10, 10, -100}, 1}, mirror}};

    EXPECT_EQ(0u, traceCentralRay(spheres, light));

    std::swap(spheres[0], spheres[1]);

    EXPECT_EQ(0u, traceCentralRay(spheres, light));

    std::swap(spheres[1], spheres[2]);

    EXPECT_EQ(0u, traceCentralRay(spheres, light));
}

TEST_F(RaytraceTest, objects_should_obstruct_light_sources)
{
    Light light{{{5, 0, 3}, 1}, 255};
    Spheres spheres{
        {{{-1, 0, 4}, std::sqrt(Float(2))}, mirror},
        {{{3, 0, 3}, 1}, mirror}};
    EXPECT_EQ(0u, traceCentralRay(spheres, light));
}

TEST_F(RaytraceTest, light_sources_should_obstruct_objects)
{
    Light light{{{0, 0, 10}, 1}, 255};
    Spheres spheres{{{{0.05, 0.05, 20}, 1}, mirror}};
    EXPECT_EQ(255u, traceCentralRay(spheres, light));
}

TEST_F(RaytraceTest, objects_should_be_lit_indirectly)
{
    Light light{{{3, 0, 8}, 1}, 255};
    Spheres spheres{
        {{{-1, 0, 4}, std::sqrt(Float(2))}, mirror},
        {{{4, 0, 2}, std::sqrt(Float(2))}, mirror}};
    EXPECT_EQ(255u, traceCentralRay(spheres, light));
}

TEST_F(RaytraceTest, lights_should_have_custom_intensity)
{
    Light light{{{5, 0, 3}, 1}, 37};
    Spheres spheres{{{{-1, 0, 4}, std::sqrt(Float(2))}, mirror}};
    EXPECT_EQ(37, traceCentralRay(spheres, light));
}

TEST_F(RaytraceTest, should_saturate_light_intensity)
{
    Light light{{{5, 0, 3}, 1}, 1000};
    Spheres spheres{{{{-1, 0, 4}, std::sqrt(Float(2))}, mirror}};
    EXPECT_EQ(255, traceCentralRay(spheres, light));
}

TEST_F(RaytraceTest, materials_should_decrease_the_amount_of_reflected_light)
{
    Light light{{{5, 0, 3}, 1}, 8};
    Spheres spheres{{{{-1, 0, 4}, std::sqrt(Float(2))}, MirrorMaterial{0.625}}};
    EXPECT_EQ(8 * 0.625, traceCentralRay(spheres, light));
}

TEST_F(RaytraceTest, each_bounce_should_decrease_the_amount_of_reflected_light)
{
    Light light{{{3, 0, 8}, 1}, 16};
    Spheres spheres{
        {{{-1, 0, 4}, std::sqrt(Float(2))}, MirrorMaterial{0.75}},
        {{{4, 0, 2}, std::sqrt(Float(2))}, MirrorMaterial{0.5}}};
    EXPECT_EQ(16 * 0.75 * 0.5, traceCentralRay(spheres, light));
}

}
}
