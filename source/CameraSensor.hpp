#pragma once
#include "Ray.hpp"

namespace lc
{

struct SensorSize
{
    unsigned width, height;
};

struct CameraSensor
{
    SensorSize size;

    /**
     * @param f void(unsigned x, unsigned y, Ray ray)
     */
    template <typename F3>
    void forEachRay(F3 f)
    {
        for (unsigned y = 0; y < size.height; ++y)
            for (unsigned x = 0; x < size.width; ++x)
                f(x, y, rayFrom(x, y));
    }

private:
    Ray rayFrom(unsigned x, unsigned y) const
    {
        return {{Float(x), Float(y), 0}, {0, 0, 1}};
    }
};

}
