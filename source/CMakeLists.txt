add_definitions("-Wall")
add_definitions(-Dint_p_NULL=nullptr)

add_executable(raytrace main.cpp)
target_link_libraries(raytrace ${Boost_LIBRARIES} png)
