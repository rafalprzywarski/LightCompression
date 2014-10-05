#pragma once
#include "CameraSensor.hpp"

namespace lc
{

template <typename CameraSensor, typename Lens>
class Camera
{
public:
    Camera(CameraSensor sensor, Lens lens) : sensor(sensor), lens(lens) { }

    template <typename Intensity>
    auto collectImage(Intensity intensity)
    {
        return sensor.collectImage([=](auto ray) { return intensity(lens.refract(ray)); });
    }

    template <typename Archive>
    void serialize(Archive& a, unsigned)
    {
        a & boost::serialization::make_nvp("sensor", sensor);
        a & boost::serialization::make_nvp("lens", lens);
    }

private:
    CameraSensor sensor;
    Lens lens;
};

template <typename CameraSensor, typename Lens>
Camera<CameraSensor, Lens> createCamera(CameraSensor sensor, Lens lens)
{
    return {std::move(sensor), std::move(lens)};
}

}
