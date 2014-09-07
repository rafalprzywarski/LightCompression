#pragma once
#include "Math.hpp"
#include "Ray.hpp"

namespace lc
{

class ThinLens
{
public:
    ThinLens(Float zDistance, Float focalLength)
    : zDistance(zDistance), focalPoint{0, 0, zDistance + focalLength}, focalLength(focalLength) { }
    auto refract(Ray r) const
    {
        Point originAtLens = getLensIntersection(r);
        return Ray{originAtLens, getFocalPoint(r) - originAtLens};
    }
private:
    Float zDistance;
    Point focalPoint;
    Float focalLength;

    Point getLensIntersection(Ray r) const
    {
        auto t = (zDistance - r.getOrigin()[2]) / r.getDirection()[2];
        return r.getOrigin() + t * r.getDirection();
    }

    Point getFocalPoint(Ray r) const
    {
        auto D = r.getDirection();
        return {D[0] / D[2] * focalLength, D[1] / D[2] * focalLength, zDistance + focalLength};
    }
};

}
