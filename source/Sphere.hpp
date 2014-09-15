#pragma once
#include "geom/Sphere.hpp"

namespace lc
{

template <typename Material>
class Sphere
{
public:
    Sphere(geom::Sphere sphere) : sphere(sphere) { }
    auto reflect(Ray ray) const { return sphere.reflect(ray); }
private:
    geom::Sphere sphere;
};

template <typename Material>
using Spheres = std::vector<Sphere<Material>>;

}
