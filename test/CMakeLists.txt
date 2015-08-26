add_definitions("-Wall")

include_directories(${GoogleMock_INCLUDE_DIRS})
include_directories("../source")

add_executable(lightcompressiontest
    main.cpp
    geom/SphereTest.cpp
    scene/RaytraceTest.cpp
    CameraSensorTest.cpp
    geom/LensTest.cpp
    geom/TwoElementCameraLensTest.cpp
    geom/PlaneTest.cpp
)

target_link_libraries(lightcompressiontest ${Boost_LIBRARIES} gmock pthread)
