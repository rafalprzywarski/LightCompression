#include <vector>
#include "Raytrace.hpp"
#include "WritePng.hpp"

int main()
{
    lc::Spheres spheres = {{{128, 64, 100}, 5}, {{32, 16, 100}, 5}};
    lc::LightSources lights = {{{0, 0, 0}, 5}};
    lc::CameraSensor sensor{{256, 128}, 1};

    auto image = lc::raytraceImage(sensor, spheres, lights);
    lc::writePng(image, "scene.png");
}
