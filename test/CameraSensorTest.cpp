#include <gmock/gmock.h>
#include <CameraSensor.hpp>
#include <Distribution.hpp>
#include "RayHelpers.hpp"

using namespace testing;

namespace lc
{

struct CameraSensorTest : testing::Test
{
    struct MockIntensity
    {
        MOCK_METHOD1(intensity, std::uint8_t(Ray ray));
    };
    StrictMock<MockIntensity> mock;
    DirectRayOnly directRayOnly;
};

TEST_F(CameraSensorTest, should_evaluate_intensity_for_each_pixel)
{
    auto sensor = createCameraSensor({4, 3}, 1, directRayOnly);
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
    auto sensor = createCameraSensor({3, 5}, 0.125, directRayOnly);
    EXPECT_CALL(mock, intensity(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(mock, intensity(RayEq(Ray{{1 * 0.125, 2 * 0.125, 0}, {0, 0, 1}}))).WillOnce(Return(202));

    auto image = sensor.collectImage([this](auto ray) { return mock.intensity(ray); });
    auto v = view(image);

    EXPECT_EQ(202, v(2, 4));
}

}
