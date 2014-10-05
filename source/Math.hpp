#pragma once
#include <cml/cml.h>
#include <boost/optional.hpp>

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
