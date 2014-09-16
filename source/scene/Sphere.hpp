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
    Sphere(geom::Sphere sphere, Material material)
        : sphere(sphere), material(material) { }
    boost::optional<LightRay> reflect(LightRay ray) const
    {
        auto normal = sphere.getSurfaceNormalRay(ray);
        if (!normal)
            return {};
        return material.getReflectionRay(ray.getDirection(), *normal);
    }
private:
    geom::Sphere sphere;
    Material material;
};

template <typename Material>
using Spheres = std::vector<Sphere<Material>>;

}
}