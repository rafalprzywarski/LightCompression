#pragma once
#include <Math.hpp>
#include <Ray.hpp>

namespace lc
{

class ThinLens
{
public:
    ThinLens(Float zDistance, Float focalLength)
    : zDistance(zDistance), focalLength(focalLength) { }
    Ray refract(Ray r) const
    {
        Vector originAtLens{r.getOrigin()[0], r.getOrigin()[1], zDistance};
        Vector focalPoint = Vector{0, 0, zDistance + focalLength};
        return Ray{originAtLens, focalPoint - originAtLens};
    }
private:
    Float zDistance, focalLength;
};

}
