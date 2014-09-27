#pragma once
#include "../Math.hpp"
#include <ostream>

namespace lc
{
namespace geom
{

class Ray
{
public:
    Ray(Vector origin, Vector direction) : origin{origin}, direction{normalize(direction)} { }
    auto getOrigin() const { return origin; }
    auto getDirection() const { return direction; }
private:
    Point origin;
    Vector direction;
};

inline std::ostream& operator<<(std::ostream& os, const Ray& r)
{
    return os << "( origin: (" << r.getOrigin() << ") direction: (" << r.getDirection() << ")";
}

using OptRay = Opt<Ray>;

}
}
