#pragma once
#include <gmock/gmock.h>

namespace lc
{

MATCHER_P(RayEq, expected, "")
{
    return arg.getOrigin() == expected.getOrigin() && arg.getDirection() == expected.getDirection();
}

MATCHER_P2(RayPassesThrough, pt, eps, "")
{
    auto ptDir = pt - arg.getOrigin();
    auto dir = arg.getDirection();

    return cross(ptDir, dir).length() < eps;
}

}
