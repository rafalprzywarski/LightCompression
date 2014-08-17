#include <vector>
#include "Raytrace.hpp"
#include "WritePng.hpp"

int main()
{
    lc::Spheres spheres = {{{0, 0, 100}, 5}, {{96, 48, 100}, 5}};
    lc::LightSources lights = {{{0, 0, 0}, 5}};
    lc::CameraSensor sensor{{256, 128}, 1};
    lc::Camera camera{sensor};

    auto image = lc::raytraceImage(camera, spheres, lights);
    lc::writePng(image, "scene.png");
}
