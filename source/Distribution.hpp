#pragma once
#include "Math.hpp"

namespace lc
{

struct DirectRayOnly
{
    template <typename Intensity>
    Float collect(Point origin, Intensity intensity) const
    {
        return intensity(Ray{origin, {0, 0, 1}});
    }
};

}
