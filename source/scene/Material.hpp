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
    Float getTransfer(Vector, Vector, Vector) const { return transfer; }
private:
    Float transfer;
};

class StretchedPhongBrdf
{
public:
    StretchedPhongBrdf(Float n) : n(n) { }
    Float getTransfer(Vector incoming, Vector normal, Vector outgoing) const
    {
        auto PI = Float(3.14159265359);
        auto cn = (n + 2) / PI;
        auto NL = -dot(normal, incoming);
        auto NV = dot(normal, outgoing);
        auto LV = -dot(incoming, outgoing);
        return cn * std::pow(std::max((2 * NL * NV - LV), Float(0)), n) / std::max(NL, NV);
    }

    template <typename Archive>
    void serialize(Archive& a, unsigned)
    {
        a & boost::serialization::make_nvp("n", n);
    }
private:
    Float n;
};

struct MirrorDistribution
{
    Vector getDirection(Vector incoming, Vector normal) const
    {
        return geom::reflect(normal, incoming);
    }
};

template <typename DirectionDistribution, typename Brdf>
class BrdfMaterial
{
public:
    BrdfMaterial(DirectionDistribution directions, Brdf brdf)
        : directions(std::move(directions)), brdf(std::move(brdf)) { }
    LightRay getReflectionRay(Vector incoming, geom::Ray normal) const
    {
        auto outgoing = directions.getDirection(incoming, normal.getDirection());
        return {{normal.getOrigin(), outgoing}, brdf.getTransfer(incoming, normal.getDirection(), outgoing)};
    }

    template <typename Archive>
    void serialize(Archive& a, unsigned)
    {
        a & boost::serialization::make_nvp("directions", directions);
        a & boost::serialization::make_nvp("brdf", brdf);
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

    template <typename Archive>
    void serialize(Archive& , unsigned)
    {
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
