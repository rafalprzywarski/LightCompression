#pragma once
#include <gmock/gmock.h>

namespace lc
{

MATCHER_P(RayEq, expected, "")
{
    return arg.getOrigin() == expected.getOrigin() && arg.getDirection() == expected.getDirection();
}

}
