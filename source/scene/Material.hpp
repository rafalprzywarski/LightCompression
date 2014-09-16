#pragma once
#include "../geom/Geom.hpp"

namespace lc
{
namespace scene
{

struct MirrorMaterial
{
    LightRay getReflectionRay(Vector incoming, geom::Ray normal) const
    {
        return {normal.getOrigin(), geom::reflect(normal.getDirection(), incoming)};
    }
};

}
}
