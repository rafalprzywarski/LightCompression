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

class FixedDistribution
{
public:
    FixedDistribution(std::vector<Vector> directions) : directions(directions) {}

    template <typename Intensity>
    Float collect(Point origin, Intensity intensity) const
    {
        Float s{};
        for (auto& d : directions)
            s += intensity(Ray{origin, d});
        return s / directions.size();
    }
private:
    std::vector<Vector> directions;
};

}
