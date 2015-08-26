#pragma once
#include "Plane.hpp"

namespace lc
{
namespace geom
{

class Polyhedron
{
public:
    Polyhedron(Planes planes) : planes(std::move(planes)) { }

    OptRay getSurfaceNormalRay(Ray ray) const
    {
        OptFloat distance;
        const Plane *side = nullptr;
        for (auto& plane : planes)
        {
            auto d = plane.getDistance(ray);
            if (d && (!distance || *distance > *d))
            {
                distance = d;
                side = &plane;
            }
        }
        
        if (!distance)
            return {};

        auto intersectionPoint = ray.getOrigin() + *distance * ray.getDirection();

        for (auto& plane : planes)
            if (&plane != side && !plane.isBehind(intersectionPoint))
              return {};

        return Ray{intersectionPoint, side->getNormal()};
    }

private:
    Planes planes;
};

using Polyhedra = std::vector<Polyhedron>;

}
}
