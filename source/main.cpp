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
        {{{  0, 0, 180}, 10}},
        //{{{ 15, 0, 220}, 15}},
        //{{{ 30, 0, 260}, 15}},
    };
    using Material = lc::scene::BrdfMaterial<lc::scene::UniformDirections>;
    Material material{{}};
    lc::scene::Spheres<Material> spheres = {
        {{{31, 0, 180}, 5}, material},
        {{{80, 0, 180}, 40}, material}};
    auto scene = createScene(spheres, lights);
    lc::FixedDistribution distribution = circle(5, 16, 16);
    auto sensor = lc::createCameraSensor({256, 128}, 0.005, distribution);
    lc::geom::ThinLens lens{2, 1.9775};
    auto camera = lc::createCamera(sensor, lens);

    auto image = scene.raytraceImage(camera);
    lc::writePng(image, "scene.png");
}
