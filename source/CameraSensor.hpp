#pragma once
#include "geom/Ray.hpp"
#include "Image.hpp"

namespace lc
{

struct SensorSize
{
    unsigned width, height;
};

template <typename Distribution>
class CameraSensor
{
public:
    CameraSensor(SensorSize size, Float pixelSize, Distribution distribution)
        : size(size), pixelSize(pixelSize), distribution(distribution) { }
    template <typename Intensity>
    auto collectImage(Intensity intensity)
    {
        Image image{size.width, size.height};
        auto v = view(image);
        forEachPixel([&](auto x, auto y) { v(x, y) = saturate(distribution.collect(pointAt(x, y), intensity)); });
        return image;
    }

    template <typename Archive>
    void serialize(Archive& a, unsigned)
    {
        a & boost::serialization::make_nvp("width", size.width);
        a & boost::serialization::make_nvp("height", size.height);
        a & boost::serialization::make_nvp("pixelSize", pixelSize);
        a & boost::serialization::make_nvp("distribution", distribution);
    }

private:
    SensorSize size;
    Float pixelSize;
    Distribution distribution;

    static auto saturate(Float v)
    {
        return std::min(v, Float(255));
    }

    Point pointAt(unsigned x, unsigned y) const
    {
        return {
            (x - 0.5 * (size.width - 1)) * pixelSize,
            (y - 0.5 * (size.height - 1)) * pixelSize,
            0};
    }
    template <typename F2>
    void forEachPixel(F2 f)
    {
        for (unsigned y = 0; y < size.height; ++y)
            for (unsigned x = 0; x < size.width; ++x)
                f(x, y);
    }
};

template <typename Distribution>
CameraSensor<Distribution> createCameraSensor(SensorSize size, Float pixelSize, Distribution distribution)
{
    return {size, pixelSize, std::move(distribution)};
}


}
