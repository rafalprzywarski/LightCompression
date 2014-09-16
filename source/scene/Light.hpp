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
    auto isHitBy(LightRay ray) const { return sphere.intersects(ray); }
private:
    geom::Sphere sphere;
};

using Lights = std::vector<Light>;

}
}
