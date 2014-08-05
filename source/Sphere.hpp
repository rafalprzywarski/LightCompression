#pragma once
#include "Math.hpp"
#include "Ray.hpp"
#include <vector>

namespace lc
{

class Sphere
{
public:
    Sphere(Vector origin, Float radius) : origin{origin}, radius2{radius * radius} { }

    auto intersects(Ray ray) const
    {
        auto oc = ray.getOrigin() - origin;
        auto b = dot(ray.getDirection(), oc);
        auto c = dot(oc, oc) - radius2;
        auto delta = b * b - c;
        if (delta < 0)
            return false;
        return delta >= 0 && -2 * std::sqrt(delta) > b;
    }

private:
    Vector origin;
    Float radius2;
};

using Spheres = std::vector<Sphere>;

}
