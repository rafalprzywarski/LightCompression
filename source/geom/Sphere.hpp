#pragma once
#include "../Math.hpp"
#include "Ray.hpp"
#include "Geom.hpp"
#include <vector>
#include <boost/optional.hpp>

namespace lc
{
namespace geom
{

class Sphere
{
public:
    Sphere(Vector origin, Float radius) : origin{origin}, radius2{radius * radius} { }

    auto intersects(Ray ray) const
    {
        auto distance = getDistance(ray);
        return distance && *distance >= 0;
    }

    boost::optional<Ray> reflect(Ray ray) const
    {
        auto normal = getSurfaceNormalRay(ray);
        if (!normal)
            return {};
        return Ray{normal->getOrigin(), geom::reflect(normal->getDirection(), ray.getDirection())};
    }

    boost::optional<Ray> getSurfaceNormalRay(Ray ray) const
    {
        auto distance = getDistance(ray);
        if (!distance || *distance < 0)
            return {};
        auto intersectionPoint = ray.getOrigin() + *distance * ray.getDirection();
        auto normal = normalize(intersectionPoint - origin);
        return Ray{intersectionPoint, normal};
    }

private:
    Point origin;
    Float radius2;

    boost::optional<Float> getDistance(Ray ray) const
    {
        auto oc = ray.getOrigin() - origin;
        auto b = dot(ray.getDirection(), oc);
        auto c = dot(oc, oc) - radius2;
        auto delta = b * b - c;
        if (delta < 0)
            return {};
        return -b - std::sqrt(delta);
    }
};

using Spheres = std::vector<Sphere>;

}
}
