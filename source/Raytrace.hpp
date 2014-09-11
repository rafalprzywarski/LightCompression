#pragma once
#include "Image.hpp"
#include "Camera.hpp"
#include "Sphere.hpp"

namespace lc
{

inline auto intersects(const Spheres& spheres, const Ray& ray)
{
    return std::find_if(begin(spheres), end(spheres), [=](auto& s) { return s.intersects(ray); }) != spheres.end();
}

inline auto reflectRay(Ray ray, const Spheres& spheres)
{
    if (!spheres.empty())
        if (auto r = spheres[0].reflect(ray))
            return *r;
    return ray;
}

inline auto raytraceIntensity(Ray ray, const Spheres& spheres, const Spheres& lights)
{
    return intersects(lights, reflectRay(ray, spheres)) ? 255 : 0;
}

template <typename Camera>
inline Image raytraceImage(Camera camera, const Spheres& spheres, const Spheres& lights)
{
    return camera.collectImage([&](auto ray) { return raytraceIntensity(ray, spheres, lights); });
}

}
