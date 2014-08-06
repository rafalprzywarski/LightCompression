#pragma once
#include "Image.hpp"
#include "CameraSensor.hpp"
#include "Sphere.hpp"
#include "LightSource.hpp"

namespace lc
{

inline auto intersects(const Spheres& spheres, const Ray& ray)
{
    return std::find_if(begin(spheres), end(spheres), [=](auto& s) { return s.intersects(ray); }) != spheres.end();
}

inline auto raytraceIntensity(Ray ray, const Spheres& spheres)
{
    return intersects(spheres, ray) ? 255 : 0;
}

inline Image raytraceImage(CameraSensor sensor, const Spheres& spheres, const LightSources& lights)
{
    return sensor.collectImage([&](auto ray) { return raytraceIntensity(ray, spheres); });
}

}
