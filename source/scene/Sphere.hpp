#pragma once
#include "../geom/Sphere.hpp"

namespace lc
{
namespace scene
{

template <typename Material>
class Sphere
{
public:
    Sphere(geom::Sphere sphere) : sphere(sphere) { }
    auto reflect(LightRay ray) const { return sphere.reflect(ray); }
private:
    geom::Sphere sphere;
};

template <typename Material>
using Spheres = std::vector<Sphere<Material>>;

}
}
