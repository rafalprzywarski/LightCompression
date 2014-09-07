#include <vector>
#include "Raytrace.hpp"
#include "Lens.hpp"
#include "Distribution.hpp"
#include "WritePng.hpp"

int main()
{
    lc::Spheres spheres = {{{0, 0, 100}, 5}, {{96, 48, 100}, 5}};
    lc::LightSources lights = {{{0, 0, 0}, 5}};
    lc::DirectRayOnly distribution;
    auto sensor = lc::createCameraSensor({256, 128}, 1, distribution);
    //lc::ThinLens lens{0, 10000};
    lc::TwoElementCameraLens lens{{0, 1}, {2, 1}};
    auto camera = lc::createCamera(sensor, lens);

    auto image = lc::raytraceImage(camera, spheres, lights);
    lc::writePng(image, "scene.png");
}
