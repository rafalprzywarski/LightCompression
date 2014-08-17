#pragma once
#include "CameraSensor.hpp"

namespace lc
{

class Camera
{
public:
    explicit Camera(CameraSensor sensor) : sensor(sensor) { }

    template <typename Intensity>
    auto collectImage(Intensity intensity)
    {
        return sensor.collectImage(intensity);
    }
private:
    CameraSensor sensor;
};

}
