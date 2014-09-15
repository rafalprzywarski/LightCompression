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

    auto reflectRay(Ray ray)
    {
        if (!spheres.empty())
            if (auto r = spheres[0].reflect(ray))
                return *r;
        return ray;
    }

    auto doesHitAnyLight(const Ray& ray)
    {
        return std::find_if(
            begin(lights), end(lights),
            [=](auto& s) { return s.isHitBy(ray); }) != lights.end();
    }


    Float raytraceIntensity(Ray ray)
    {
        return doesHitAnyLight(reflectRay(ray)) ? 255 : 0;
    }
};

template <typename Spheres>
Scene<Spheres> createScene(Spheres spheres, Lights lights)
{
    return {std::move(spheres), std::move(lights)};
}


}
}
