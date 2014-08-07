#pragma once
#include "Math.hpp"
#include <vector>

namespace lc
{

struct LightSource
{
    Point origin;
    Float radius;
};

using LightSources = std::vector<LightSource>;

}
