#pragma once
#include "Image.hpp"

namespace lc
{

Image raytrace(CameraSensor sensor, const Spheres& spheres)
{
    return Image{sensor.size.width, sensor.size.height};
}

}
