#pragma once
#include <cml/cml.h>
#include <boost/optional.hpp>
#include <boost/serialization/vector.hpp>

namespace lc
{

typedef double Float;
typedef cml::vector<Float, cml::fixed<3>> Vector;
typedef Vector Point;

template <typename T>
using Opt = boost::optional<T>;

template <typename T, typename M>
inline Opt<M> getOpt(const Opt<T>& o, const M T::*m)
{
    if (!o)
        return {};
    return (*o).*m;
}

using OptFloat = Opt<Float>;

}

namespace boost
{
namespace serialization
{

template <typename Archive>
void serialize(Archive& a, lc::Point& p, unsigned)
{
    a & boost::serialization::make_nvp("x", p[0]);
    a & boost::serialization::make_nvp("y", p[1]);
    a & boost::serialization::make_nvp("z", p[2]);
}

}
}
