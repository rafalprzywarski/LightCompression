#pragma once
#include "Light.hpp"

namespace lc
{
namespace scene
{

template <typename... Objects>
class Scene
{
public:
    Scene(Lights lights, Objects... objects)
        : objects(std::move(objects)...), lights(std::move(lights)) { }

    template <typename Camera>
    auto raytraceImage(Camera camera)
    {
        return camera.collectImage([&](auto ray) { return raytraceIntensity(ray); });
    }
private:
    std::tuple<Objects...> objects;
    Lights lights;

    template <std::size_t I = 0, typename F, typename... T>
    typename std::enable_if<I == sizeof...(T), void>::type forEach(std::tuple<T...> &, F) { }

    template<std::size_t I = 0, typename F, typename... T>
    typename std::enable_if<I < sizeof...(T), void>::type forEach(std::tuple<T...>& t, F f)
    {
        f(std::get<I>(t));
        forEach<I + 1, F, T...>(t, f);
    }

    Opt<LightRay> getReflectedRay(LightRay ray)
    {
        Opt<LightRay> reflected;
        forEach(objects, [&reflected, &ray](auto objects)
        {
            for (auto& o : objects)
                if (auto r = o.reflect(ray))
                    if (!reflected ||
                        (ray.getOrigin() - reflected->getOrigin()).length_squared() >
                        (ray.getOrigin() - r->getOrigin()).length_squared())
                        reflected = *r;
        });
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

template <typename... Objects>
Scene<Objects...> createScene(Lights lights, Objects... objects)
{
    return {std::move(lights), std::move(objects)...};
}

}
}
