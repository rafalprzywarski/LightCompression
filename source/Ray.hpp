#pragma once
#include "Math.hpp"

namespace lc
{

class Ray
{
public:
    Ray(Vector origin, Vector direction) : origin{origin}, direction{normalize(direction)} { }
    auto getOrigin() const { return origin; }
    auto getDirection() const { return direction; }
private:
    Vector origin, direction;
};

}
