#include <vector>
#include "Raytrace.hpp"
#include "Lens.hpp"
#include "Distribution.hpp"
#include "WritePng.hpp"

lc::FixedDistribution circle(lc::Float radius, unsigned N)
{
    std::vector<lc::Vector> dirs;
    for (unsigned y = 0; y < N; ++y)
        for (unsigned x = 0; x < N; ++x)
        {
            lc::Point p{(lc::Float(x) / N - 0.5) * radius, (lc::Float(y) / N - 0.5) * radius, 0};
            if (p.length() > radius)
                continue;
            p[2] = 1;
            dirs.push_back(p);
        }
    return dirs;
}

int main()
{
    lc::Spheres spheres = {
        {{-30, 0, 100}, 15},
        {{-15, 0, 140}, 15},
        {{  0, 0, 180}, 15},
        {{ 15, 0, 220}, 15},
        {{ 30, 0, 260}, 15},
    };
    lc::LightSources lights = {{{0, 0, 0}, 5}};
    lc::FixedDistribution distribution = circle(10, 32);
    auto sensor = lc::createCameraSensor({1024, 512}, 0.0025, distribution);
    lc::ThinLens lens{2, 1.9775};
    auto camera = lc::createCamera(sensor, lens);

    auto image = lc::raytraceImage(camera, spheres, lights);
    lc::writePng(image, "scene.png");
}
