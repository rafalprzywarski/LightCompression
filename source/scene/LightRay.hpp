#pragma once
#include "../geom/Ray.hpp"

namespace lc
{
namespace scene
{

class LightRay : public geom::Ray
{
public:
    using geom::Ray::Ray;
    LightRay(const Ray& ray, Float intensity = 1)
    : geom::Ray(ray), intensity(intensity) {}
    Float getIntensity() const { return intensity; }
    LightRay getTransfered(Float factory) { return {*this, this->intensity * factory}; }
private:
    Float intensity;
};

}
}
