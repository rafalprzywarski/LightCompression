#pragma once
#include "Image.hpp"
#include "Camera.hpp"
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

template <typename Camera>
inline Image raytraceImage(Camera camera, const Spheres& spheres, const LightSources& lights)
{
    return camera.collectImage([&](auto ray) { return raytraceIntensity(ray, spheres); });
}

}
