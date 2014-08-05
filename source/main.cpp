#include <vector>
#include "CameraSensor.hpp"
#include "Sphere.hpp"
#include "Raytrace.hpp"
#include "WritePng.hpp"

int main()
{
    lc::Spheres spheres;
    lc::CameraSensor sensor{{128, 64}};

    auto image = lc::raytrace(sensor, spheres);
    lc::writePng(image, "scene.png");
}
