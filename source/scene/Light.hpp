#pragma once
#include "../geom/Sphere.hpp"

namespace lc
{
namespace scene
{

class Light
{
public:
    Light(geom::Sphere sphere) : sphere(sphere) { }
    auto isHitBy(Ray ray) const { return sphere.intersects(ray); }
private:
    geom::Sphere sphere;
};

using Lights = std::vector<Light>;

}
}
