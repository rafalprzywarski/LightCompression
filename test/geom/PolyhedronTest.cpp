#include <gtest/gtest.h>
#include <geom/Polyhedron.hpp>
#include "RayHelpers.hpp"

using namespace testing;

namespace lc
{
namespace geom
{

struct PolyhedronTest : testing::Test
{
    Float EPS = 1e-5;

    Planes planes{ // cube 2x2x2
      {{1, 0, 0}, 1},
      {{-1, 0, 0}, 1},
      {{0, 1, 0}, 1},
      {{0, -1, 0}, 1},
      {{0, 0, 1}, 1},
      {{0, 0, -1}, 1}
    };
    Polyhedron cube{planes};
};

TEST_F(PolyhedronTest, should_provide_surface_normal_when_ray_hits)
{
    EXPECT_THAT(*cube.getSurfaceNormalRay({{10, 0, 0}, {-1, 0, 0}}), AllOf(RayHasOrigin(Vector{1, 0, 0}, EPS), RayHasDirection(planes[0].getNormal(), EPS)));
    EXPECT_THAT(*cube.getSurfaceNormalRay({{-10, 0, 0}, {1, 0, 0}}), AllOf(RayHasOrigin(Vector{-1, 0, 0}, EPS), RayHasDirection(planes[1].getNormal(), EPS)));
    EXPECT_THAT(*cube.getSurfaceNormalRay({{0, 10, 0}, {0, -1, 0}}), AllOf(RayHasOrigin(Vector{0, 1, 0}, EPS), RayHasDirection(planes[2].getNormal(), EPS)));
    EXPECT_THAT(*cube.getSurfaceNormalRay({{0, -10, 0}, {0, 1, 0}}), AllOf(RayHasOrigin(Vector{0, -1, 0}, EPS), RayHasDirection(planes[3].getNormal(), EPS)));
    EXPECT_THAT(*cube.getSurfaceNormalRay({{0, 0, 10}, {0, 0, -1}}), AllOf(RayHasOrigin(Vector{0, 0, 1}, EPS), RayHasDirection(planes[4].getNormal(), EPS)));
    EXPECT_THAT(*cube.getSurfaceNormalRay({{0, 0, -10}, {0, 0, 1}}), AllOf(RayHasOrigin(Vector{0, 0, -1}, EPS), RayHasDirection(planes[5].getNormal(), EPS)));

    EXPECT_THAT(*cube.getSurfaceNormalRay({{1, 2, 0}, {-1, -1, 0}}), AllOf(RayHasOrigin(Vector{0, 1, 0}, EPS), RayHasDirection(planes[2].getNormal(), EPS)));
}

TEST_F(PolyhedronTest, should_not_provide_surface_normal_when_ray_does_not_hit)
{
  EXPECT_FALSE(cube.getSurfaceNormalRay({{10, 2, 0}, {-1, 0, 0}}));
  EXPECT_FALSE(cube.getSurfaceNormalRay({{10, -2, 0}, {-1, 0, 0}}));
  EXPECT_FALSE(cube.getSurfaceNormalRay({{10, 0, 2}, {-1, 0, 0}}));
  EXPECT_FALSE(cube.getSurfaceNormalRay({{10, 0, -2}, {-1, 0, 0}}));
  EXPECT_FALSE(cube.getSurfaceNormalRay({{3, 0, 0}, {-1, -1, 0}}));
}

}
}
