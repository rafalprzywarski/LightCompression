#pragma once
#include "Image.hpp"
#include "CameraSensor.hpp"
#include "Sphere.hpp"

namespace lc
{

inline auto intersects(const Spheres& spheres, const Ray& ray)
{
    return std::find_if(begin(spheres), end(spheres), [=](auto& s) { return s.intersects(ray); }) != spheres.end();
}

inline Image raytrace(CameraSensor sensor, const Spheres& spheres)
{
    Image image{sensor.size.width, sensor.size.height};
    auto v = view(image);
    sensor.forEachRay([&](auto x, auto y, auto ray) { v(x, y) = intersects(spheres, ray) ? 255 : 0; });
    return image;
}

}
