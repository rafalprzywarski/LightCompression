add_definitions("-Wall")
add_definitions(-Dint_p_NULL=nullptr)

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIRS})

add_executable(raytrace main.cpp)
target_link_libraries(raytrace ${Boost_LIBRARIES} ${PNG_LIBRARIES})
