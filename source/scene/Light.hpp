#pragma once
#include "../geom/Sphere.hpp"
#include "LightRay.hpp"

namespace lc
{
namespace scene
{

class Light
{
public:
    Light(geom::Sphere sphere) : sphere(sphere) { }
    OptFloat getIntensity(LightRay ray, OptFloat distance2) const
    {
        if (!sphere.intersects(ray) ||
            (distance2 &&
                (ray.getOrigin() - sphere.getSurfaceNormalRay(ray)->getOrigin()).length_squared() >
                    distance2)) return {};
        return 255;
    }
private:
    geom::Sphere sphere;
};

using Lights = std::vector<Light>;

}
}
