#pragma once
#include "Light.hpp"

namespace lc
{
namespace scene
{

template <typename Spheres>
class Scene
{
public:
    Scene(Spheres spheres, Lights lights)
        : spheres(std::move(spheres)), lights(std::move(lights)) { }

    template <typename Camera>
    auto raytraceImage(Camera camera)
    {
        return camera.collectImage([&](auto ray) { return raytraceIntensity(ray); });
    }
private:
    Spheres spheres;
    Lights lights;

    Opt<LightRay> getReflectedRay(LightRay ray)
    {
        Opt<LightRay> reflected;
        for (auto& s : spheres)
            if (auto r = s.reflect(ray))
                if (!reflected || reflected->getOrigin()[2] > r->getOrigin()[2])
                    reflected = *r;
        return reflected;
    }

    struct LightRayWithDistance2
    {
        LightRay ray;
        Float distance2;
    };

    Opt<LightRayWithDistance2> getReflectedRayWithDistance2(LightRay ray)
    {
        if (auto r = getReflectedRay(ray))
            return LightRayWithDistance2{*r, (ray.getOrigin() - r->getOrigin()).length_squared()};
        return {};
    }

    OptFloat getLightIntensityWithin(const LightRay& ray, const OptFloat& distance2)
    {
        for (auto& l : lights)
            if (auto i = l.getIntensity(ray, distance2))
                return i;
        return {};
    }


    Float raytraceIntensity(LightRay ray)
    {
        while (true)
        {
            Opt<LightRayWithDistance2> rd = getReflectedRayWithDistance2(ray);
            if (auto i = getLightIntensityWithin(ray, getOpt(rd, &LightRayWithDistance2::distance2)))
                return *i * ray.getIntensity();
            if (!rd)
                return 0;
            ray = rd->ray;
        }
    }
};

template <typename Spheres>
Scene<Spheres> createScene(Spheres spheres, Lights lights)
{
    return {std::move(spheres), std::move(lights)};
}


}
}
