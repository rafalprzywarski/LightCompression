#pragma once
#include "Image.hpp"
#include "Camera.hpp"
#include "Sphere.hpp"

namespace lc
{

class Scene
{
public:
    Scene(Spheres spheres, Spheres lights)
        : spheres(std::move(spheres)), lights(std::move(lights)) { }

    template <typename Camera>
    Image raytraceImage(Camera camera)
    {
        return camera.collectImage([&](auto ray) { return raytraceIntensity(ray); });
    }
private:
    Spheres spheres, lights;

    auto reflectRay(Ray ray)
    {
        if (!spheres.empty())
            if (auto r = spheres[0].reflect(ray))
                return *r;
        return ray;
    }

    auto intersects(const Ray& ray)
    {
        return std::find_if(
            begin(lights), end(lights),
            [=](auto& s) { return s.intersects(ray); }) != lights.end();
    }


    Float raytraceIntensity(Ray ray)
    {
        return intersects(reflectRay(ray)) ? 255 : 0;
    }
};

}
