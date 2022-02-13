cmake_minimum_required(VERSION 3.15)
project(graphx_lib)

set(CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS ON)

# Store into S_FILES variable all .c file that was on the src folder
file(GLOB_RECURSE S_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/**.cpp)

if(APPLE)
    # Store into M_FILES variable all .m file that was on the src folder
    file(GLOB_RECURSE M_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/**.m)
    list(APPEND S_FILES ${M_FILES})
endif()

# Store all .h files in the src folder into a variable named "H_FILES"
file(GLOB_RECURSE H_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/**.hpp)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/gfx)

add_library(GraphXLib STATIC ${S_FILES} ${H_FILES} ${M_FILES})

target_include_directories(GraphXLib
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(GraphXLib
    PUBLIC GraphX
    PRIVATE glfw
    PRIVATE cglm
)

add_subdirectory(sample)