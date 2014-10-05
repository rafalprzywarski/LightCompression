#include <gmock/gmock.h>
#include <CameraSensor.hpp>
#include <Distribution.hpp>
#include "geom/RayHelpers.hpp"

using namespace testing;

namespace lc
{

struct CameraSensorTest : testing::Test
{
    struct MockIntensity
    {
        MOCK_METHOD1(intensity, std::uint8_t(geom::Ray ray));
    };
    StrictMock<MockIntensity> mock;
    DirectRayOnly directRayOnly;
};

TEST_F(CameraSensorTest, should_evaluate_intensity_for_each_pixel)
{
    using geom::Ray;
    auto sensor = createCameraSensor({4, 3}, {0, 0}, 1, directRayOnly);
    EXPECT_CALL(mock, intensity(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(mock, intensity(RayEq(Ray{{-1.5, -1, 0}, {0, 0, 1}}))).WillOnce(Return(101));
    EXPECT_CALL(mock, intensity(RayEq(Ray{{ 1.5, -1, 0}, {0, 0, 1}}))).WillOnce(Return(201));
    EXPECT_CALL(mock, intensity(RayEq(Ray{{ 1.5,  1, 0}, {0, 0, 1}}))).WillOnce(Return(202));
    EXPECT_CALL(mock, intensity(RayEq(Ray{{-1.5,  1, 0}, {0, 0, 1}}))).WillOnce(Return(102));
    EXPECT_CALL(mock, intensity(RayEq(Ray{{ 0.5,  0, 0}, {0, 0, 1}}))).WillOnce(Return(222));

    auto image = sensor.collectImage([this](auto ray) { return mock.intensity(ray); });
    auto v = view(image);

    EXPECT_EQ(101, v(0, 0));
    EXPECT_EQ(201, v(3, 0));
    EXPECT_EQ(202, v(3, 2));
    EXPECT_EQ(102, v(0, 2));
    EXPECT_EQ(222, v(2, 1));
}

TEST_F(CameraSensorTest, should_scale_pixel_size)
{
    using geom::Ray;
    auto sensor = createCameraSensor({3, 5}, {0, 0}, 0.125, directRayOnly);
    EXPECT_CALL(mock, intensity(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(mock, intensity(RayEq(Ray{{1 * 0.125, 2 * 0.125, 0}, {0, 0, 1}}))).WillOnce(Return(202));

    auto image = sensor.collectImage([this](auto ray) { return mock.intensity(ray); });
    auto v = view(image);

    EXPECT_EQ(202, v(2, 4));
}

TEST_F(CameraSensorTest, should_use_the_distribution)
{
    Vector DIR1{1, 0, 0}, DIR2{0, 1, 0}, DIR3{0, 0, 1};
    FixedDistribution distribution{{DIR1, DIR2, DIR3}};
    auto sensor = createCameraSensor({1, 1}, {0, 0}, 1, distribution);

    EXPECT_CALL(mock, intensity(RayHasDirection(DIR1, 0))).WillOnce(Return(1 * 3));
    EXPECT_CALL(mock, intensity(RayHasDirection(DIR2, 0))).WillOnce(Return(2 * 3));
    EXPECT_CALL(mock, intensity(RayHasDirection(DIR3, 0))).WillOnce(Return(4 * 3));

    auto image = sensor.collectImage([this](auto ray) { return mock.intensity(ray); });

    EXPECT_EQ(1 + 2 + 4, view(image)(0, 0));
}

TEST_F(CameraSensorTest, should_offset_pixels_by_given_coordinates)
{
    using geom::Ray;
    auto sensor = createCameraSensor({4, 3}, {13, -17}, 1, directRayOnly);
    EXPECT_CALL(mock, intensity(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(mock, intensity(RayEq(Ray{{-1.5 + 13, -1 - 17, 0}, {0, 0, 1}}))).WillOnce(Return(101));
    EXPECT_CALL(mock, intensity(RayEq(Ray{{ 0.5 + 13,  0 - 17, 0}, {0, 0, 1}}))).WillOnce(Return(222));

    auto image = sensor.collectImage([this](auto ray) { return mock.intensity(ray); });
    auto v = view(image);

    EXPECT_EQ(101, v(0, 0));
    EXPECT_EQ(222, v(2, 1));
}

}
