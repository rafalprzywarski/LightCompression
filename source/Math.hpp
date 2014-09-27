#include <cml/cml.h>
#include <boost/optional.hpp>

namespace lc
{

typedef double Float;
typedef cml::vector<Float, cml::fixed<3>> Vector;
typedef Vector Point;

template <typename T>
using Opt = boost::optional<T>;

using OptFloat = Opt<Float>;

}
