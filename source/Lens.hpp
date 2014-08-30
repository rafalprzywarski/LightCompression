#pragma once
#include "Math.hpp"
#include "Ray.hpp"

namespace lc
{

class ThinLens
{
public:
    ThinLens(Float zDistance, Float focalLength)
    : zDistance(zDistance), focalPoint{0, 0, zDistance + focalLength} { }
    auto refract(Ray r) const
    {
        Point originAtLens{r.getOrigin()[0], r.getOrigin()[1], zDistance};
        return Ray{originAtLens, focalPoint - originAtLens};
    }
private:
    Float zDistance;
    Point focalPoint;
};

}
