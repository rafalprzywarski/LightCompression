#pragma once
#include "../geom/Geom.hpp"

namespace lc
{
namespace scene
{

struct MirrorDistribution
{
    Vector getDirection(Vector incoming, Vector normal) const
    {
        return geom::reflect(normal, incoming);
    }
};

template <typename DirectionDistribution>
class BrdfMaterial
{
public:
    BrdfMaterial(DirectionDistribution directions)
        : directions(std::move(directions)) { }
    LightRay getReflectionRay(Vector incoming, geom::Ray normal) const
    {
        return {normal.getOrigin(), directions.getDirection(incoming, normal.getDirection())};
    }
private:
    DirectionDistribution directions;
};

struct MirrorMaterial : BrdfMaterial<MirrorDistribution>
{
    MirrorMaterial() : BrdfMaterial({}) { }
};

}
}
