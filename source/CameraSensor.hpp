#pragma once
#include "Ray.hpp"
#include "Image.hpp"

namespace lc
{

struct SensorSize
{
    unsigned width, height;
};

struct CameraSensor
{
    SensorSize size;

    template <typename Intensity>
    auto collectImage(Intensity intensity)
    {
        Image image{size.width, size.height};
        auto v = view(image);
        forEachPixel([&](auto x, auto y) { v(x, y) = intensity(rayFrom(x, y)); });
        return image;
    }

private:
    Ray rayFrom(unsigned x, unsigned y) const
    {
        return {{Float(x), Float(y), 0}, {0, 0, 1}};
    }
    template <typename F2>
    void forEachPixel(F2 f)
    {
        for (unsigned y = 0; y < size.height; ++y)
            for (unsigned x = 0; x < size.width; ++x)
                f(x, y);
    }
};

}
