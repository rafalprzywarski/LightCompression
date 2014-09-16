#include <vector>
#include "scene/Scene.hpp"
#include "scene/Sphere.hpp"
#include "Camera.hpp"
#include "geom/Lens.hpp"
#include "Distribution.hpp"
#include "WritePng.hpp"

lc::FixedDistribution circle(lc::Float radius, unsigned N)
{
    std::vector<lc::Vector> dirs;
    for (unsigned y = 0; y < N; ++y)
        for (unsigned x = 0; x < N; ++x)
        {
            lc::Point p{(lc::Float(x) / N - 0.5) * radius * 2, (lc::Float(y) / N - 0.5) * radius * 2, 0};
            if (p.length() > radius)
                continue;
            p[2] = 1;
            dirs.push_back(p);
        }
    return dirs;
}

int main()
{
    lc::scene::Lights lights = {
        {{{-30, 0, 100}, 15}},
        {{{-15, 0, 140}, 15}},
        {{{  0, 0, 180}, 15}},
        {{{ 15, 0, 220}, 15}},
        {{{ 30, 0, 260}, 15}},
    };
    lc::scene::Spheres<void> spheres = {{{{30, 0, 180}, 15}}};
    auto scene = createScene(spheres, lights);
    lc::FixedDistribution distribution = circle(5, 12);
    auto sensor = lc::createCameraSensor({512, 256}, 0.0045, distribution);
    lc::geom::ThinLens lens{2, 1.9775};
    auto camera = lc::createCamera(sensor, lens);

    auto image = scene.raytraceImage(camera);
    lc::writePng(image, "scene.png");
}
