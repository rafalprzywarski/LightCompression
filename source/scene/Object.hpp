#pragma once
#include "../geom/Sphere.hpp"

namespace lc
{
namespace scene
{

template <typename Shape, typename Material>
class Object
{
public:
    Object(Shape shape, Material material)
        : shape(shape), material(material) { }
    Opt<LightRay> reflect(LightRay ray) const
    {
        auto normal = shape.getSurfaceNormalRay(ray);
        if (!normal)
            return {};
        return material.getReflectionRay(ray.getDirection(), *normal).getTransfered(ray.getIntensity());
    }
private:
    Shape shape;
    Material material;
};

template <typename Material>
using Sphere = Object<geom::Sphere, Material>;

template <typename Material>
using Spheres = std::vector<Sphere<Material>>;

}
}
