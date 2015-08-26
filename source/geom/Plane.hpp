#pragma once
#include "../Math.hpp"
#include "Ray.hpp"
#include "Geom.hpp"
#include <vector>

namespace lc
{
namespace geom
{

class Plane
{
public:
    Plane(Vector normal, Float d) : normal(normalize(normal)), d(d) { }

    Vector getNormal() const { return normal; }

    OptFloat getDistance(Ray ray) const
    {
        auto DN = dot(ray.getDirection(), normal);
        if (DN >= 0)
            return {};
        auto distance = (d - dot(ray.getOrigin(), normal)) / DN;
        if (distance <= 0)
          return {};
        return distance;
    }

    bool isBehind(Point p) const
    {
        return dot(p, normal) < d;
    }

private:
    Vector normal;
    Float d;
};

using Planes = std::vector<Plane>;

}
}
