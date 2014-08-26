#pragma once
#include <Math.hpp>
#include <Ray.hpp>

namespace lc
{

class ThinLens
{
public:
    ThinLens(Float zDistance, Float invR1, Float invR2) { }
    auto refract(Ray r) const { return r; }
};

}
