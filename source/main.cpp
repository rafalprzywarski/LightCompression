#include <vector>
#include "scene/Scene.hpp"
#include "scene/Sphere.hpp"
#include "Camera.hpp"
#include "geom/Lens.hpp"
#include "Distribution.hpp"
#include "scene/Material.hpp"
#include "WritePng.hpp"

lc::FixedDistribution circle(lc::Float radius, unsigned N, unsigned S)
{
    std::vector<lc::Vector> dirs;
    for (unsigned y = 0; y < N; ++y)
        for (unsigned x = 0; x < N; ++x)
        {
            lc::Point p{(lc::Float(x) / N - 0.5) * radius * 2, (lc::Float(y) / N - 0.5) * radius * 2, 0};
            if (p.length() > radius)
                continue;
            p[2] = 1;
            for (unsigned i = 0; i < S; ++i)
                dirs.push_back(p);
        }
    return dirs;
}

int main()
{
    lc::scene::Lights lights = {
        //{{{-30, 0, 100}, 15}},
        //{{{-15, 0, 140}, 15}},
        {{{  -80, 0, 200}, 10}, 12000},
        //{{{ 15, 0, 220}, 15}},
        //{{{ 30, 0, 260}, 15}},
    };
    using Material = lc::scene::BrdfMaterial<lc::scene::UniformDirections, lc::scene::StretchedPhongBrdf>;
    Material material{{}, {100}};
    lc::scene::Spheres<Material> spheres = {
        {{{-10, 0, 180}, 5}, Material{{}, {40}}},
        {{{0, 10, 220}, 5}, Material{{}, {20}}},
        {{{-10, 10, 240}, 5}, Material{{}, {20}}},
        {{{-20, 10, 260}, 5}, Material{{}, {20}}},
        {{{40, 0, 200}, 40}, Material{{}, {4}}}};
    auto scene = createScene(spheres, lights);
    lc::FixedDistribution distribution = circle(0.05, 2, 8192 * 4);
    auto sensor = lc::createCameraSensor({1024, 512}, 0.000625, distribution);
    lc::geom::ThinLens lens{2, 1.9775};
    auto camera = lc::createCamera(sensor, lens);

    auto image = scene.raytraceImage(camera);
    lc::writePng(image, "scene.png");
}
