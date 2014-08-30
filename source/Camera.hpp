#pragma once
#include "CameraSensor.hpp"
#include "Lens.hpp"

namespace lc
{

class Camera
{
public:
    explicit Camera(CameraSensor sensor, ThinLens lens) : sensor(sensor), lens(lens) { }

    template <typename Intensity>
    auto collectImage(Intensity intensity)
    {
        return sensor.collectImage([=](auto ray) { return intensity(lens.refract(ray)); });
    }
private:
    CameraSensor sensor;
    ThinLens lens;
};

}
