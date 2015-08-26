#pragma once
#include "Light.hpp"

namespace lc
{
namespace scene
{

template <typename Objects>
class Scene
{
public:
    Scene(Objects objects, Lights lights)
        : objects(std::move(objects)), lights(std::move(lights)) { }

    template <typename Camera>
    auto raytraceImage(Camera camera)
    {
        return camera.collectImage([&](auto ray) { return raytraceIntensity(ray); });
    }
private:
    Objects objects;
    Lights lights;

    Opt<LightRay> getReflectedRay(LightRay ray)
    {
        Opt<LightRay> reflected;
        for (auto& o : objects)
            if (auto r = o.reflect(ray))
                if (!reflected ||
                    (ray.getOrigin() - reflected->getOrigin()).length_squared() >
                    (ray.getOrigin() - r->getOrigin()).length_squared())
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

template <typename Objects>
Scene<Objects> createScene(Objects objects, Lights lights)
{
    return {std::move(objects), std::move(lights)};
}


}
}
