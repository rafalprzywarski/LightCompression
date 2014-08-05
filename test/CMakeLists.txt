include_directories(${GoogleMock_INCLUDE_DIRS})
include_directories("../source")

add_executable(lightcompressiontest main.cpp SphereTest.cpp)
target_link_libraries(lightcompressiontest ${Boost_LIBRARIES} gmock pthread)
