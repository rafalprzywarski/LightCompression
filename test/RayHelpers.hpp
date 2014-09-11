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
    auto ptDir = arg.getOrigin() - pt;
    auto dir = arg.getDirection();
    auto distance = cross(ptDir, dir).length();
    *result_listener << "missed by " << distance;
    return distance < eps;
}

MATCHER_P2(RayHasDirection, dir, eps, "")
{
    return cross(arg.getDirection(), dir).length() <= eps && dot(arg.getDirection(), dir) > 0;
}

MATCHER_P2(RayHasOrigin, orig, eps, "")
{
    return (arg.getOrigin() - orig).length() <= eps;
}

}
