#pragma once
#include "Math.hpp"
#include "Ray.hpp"

namespace lc
{

class ThinLens
{
public:
    ThinLens(Float zDistance, Float focalLength)
    : zDistance(zDistance), focalLength(focalLength) { }
    auto refract(Ray r) const
    {
        Point originAtLens = getLensIntersection(r);
        return Ray{originAtLens, getFocalPoint(r.getDirection()) - originAtLens};
    }
private:
    Float zDistance;
    Float focalLength;

    Point getLensIntersection(Ray r) const
    {
        auto orig = r.getOrigin();
        auto dir = r.getDirection();
        auto dist = (zDistance - orig[2]) / dir[2];
        return {orig[0] + dist * dir[0], orig[1] + dist * dir[1], zDistance};
    }

    Point getLocalFocalPoint(Vector dir) const
    {
        using std::abs;
        return dir * (focalLength / abs(dir[2]));
    }
    Point getFocalPoint(Vector dir) const
    {
        auto focalPoint = getLocalFocalPoint(dir);
        focalPoint[2] += zDistance;
        return focalPoint;
    }
};

}
