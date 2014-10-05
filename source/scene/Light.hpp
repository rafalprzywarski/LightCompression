#pragma once
#include "../geom/Sphere.hpp"
#include "LightRay.hpp"
#include <boost/serialization/vector.hpp>

namespace lc
{
namespace scene
{

class Light
{
public:
    Light(geom::Sphere sphere, Float intensity)
    : sphere(sphere), intensity(intensity) { }
    OptFloat getIntensity(LightRay ray, OptFloat distance2) const
    {
        if (!sphere.intersects(ray) ||
            (distance2 &&
                (ray.getOrigin() - sphere.getSurfaceNormalRay(ray)->getOrigin()).length_squared() >
                    distance2)) return {};
        return intensity;
    }
    template <typename Archive>
    void serialize(Archive& a, unsigned)
    {
        a & boost::serialization::make_nvp("geom", sphere);
        a & boost::serialization::make_nvp("intensity", intensity);
    }
private:
    geom::Sphere sphere;
    Float intensity;
};

using Lights = std::vector<Light>;

}
}
