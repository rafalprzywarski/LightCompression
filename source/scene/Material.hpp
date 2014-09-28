#pragma once
#include "../geom/Geom.hpp"
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_on_sphere.hpp>

namespace lc
{
namespace scene
{

class ConstantBrdf
{
public:
    ConstantBrdf(Float transfer) : transfer(transfer) { }
    Float getTransfer() const { return transfer; }
private:
    Float transfer;
};

struct MirrorDistribution
{
    Vector getDirection(Vector incoming, Vector normal) const
    {
        return geom::reflect(normal, incoming);
    }
};

template <typename DirectionDistribution, typename Brdf = ConstantBrdf>
class BrdfMaterial
{
public:
    BrdfMaterial(DirectionDistribution directions, Brdf brdf = {1})
        : directions(std::move(directions)), brdf(std::move(brdf)) { }
    LightRay getReflectionRay(Vector incoming, geom::Ray normal) const
    {
        return {{normal.getOrigin(), directions.getDirection(incoming, normal.getDirection())}, brdf.getTransfer()};
    }
private:
    DirectionDistribution directions;
    Brdf brdf;
};

struct MirrorMaterial : BrdfMaterial<MirrorDistribution, ConstantBrdf>
{
    MirrorMaterial(Float reflectivity = 1) : BrdfMaterial({}, {reflectivity}) { }
};

struct UniformDirections
{
public:
    Vector getDirection(Vector, Vector normal) const
    {
        Vector d = uos(rng);
        return dot(d, normal) < 0 ? -d : d;
    }
private:

    struct VectorWrapper : Vector
    {
        VectorWrapper(int) : Vector{} { }
        auto begin() { return &(*this)[0]; }
        auto end() { return begin() + 3; }
        using iterator = Float *;
    };

    mutable boost::random::uniform_on_sphere<Float, VectorWrapper> uos{3};
    mutable boost::random::mt19937 rng;
};

}
}
