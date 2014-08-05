#pragma once
#include <boost/gil/image.hpp>
#include <boost/gil/typedefs.hpp>

namespace lc
{

struct SensorSize
{
    unsigned width, height;
};

struct CameraSensor
{
    SensorSize size;
};

}
