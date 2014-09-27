#pragma once
#include "Math.hpp"

namespace lc
{

struct DirectRayOnly
{
    template <typename Intensity>
    Float collect(Point origin, Intensity intensity) const
    {
        return intensity(geom::Ray{origin, {0, 0, 1}});
    }
};

class RepeatedDirectRay
{
public:
    RepeatedDirectRay(unsigned N) : N(N) {}
    template <typename Intensity>
    Float collect(Point origin, Intensity intensity) const
    {
        Float s{};
        for (unsigned i = 0; i < N; ++i)
            s += intensity(geom::Ray{origin, {0, 0, 1}});
        return s / N;

    }
private:
    int N;
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
            s += intensity(geom::Ray{origin, d});
        return s / directions.size();
    }
private:
    std::vector<Vector> directions;
};

}
