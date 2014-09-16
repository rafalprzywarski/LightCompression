#pragma once
#include "../Math.hpp"

namespace lc
{
namespace geom
{

inline Vector reflect(Vector normal, Vector direction)
{
    return direction - dot(normal, direction) * 2 * normal;
}

}
}
