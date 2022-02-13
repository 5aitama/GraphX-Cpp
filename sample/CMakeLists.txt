cmake_minimum_required(VERSION 3.15)
project(graphx_sample_cpp)

set(CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS ON)

# Store into S_FILES variable all .c file that was on the src folder
file(GLOB_RECURSE S_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/**.cpp)

if(APPLE)
    # Store into M_FILES variable all .m file that was on the src folder
    file(GLOB_RECURSE M_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/**.m)
    list(APPEND S_FILES ${M_FILES})

    message("${S_FILES}")
endif()

# Store all .h files in the src folder into a variable named "H_FILES"
file(GLOB_RECURSE H_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/**.hpp)

# Store all .wgsl files in the current source directory into a variable named "SHADER_FILES"
file(GLOB_RECURSE SHADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/**.wgsl)

if(MSVC)
    set(EXTRA_PATH "Debug/")
else()
    set(EXTRA_PATH "")
endif()

message("Extra path : ${EXTRA_PATH}")

# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/gfx)
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/cglm)

file(REMOVE_RECURSE "${CMAKE_CURRENT_BINARY_DIR}/${EXTRA_PATH}shaders")
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${EXTRA_PATH}shaders")

foreach(SHADER_FILE ${SHADER_FILES})
    get_filename_component(FILE_NAME ${SHADER_FILE} NAME)
    file(COPY_FILE "${SHADER_FILE}" "${CMAKE_CURRENT_BINARY_DIR}/${EXTRA_PATH}shaders/${FILE_NAME}")
endforeach()

add_executable(graphx_sample_cpp ${S_FILES} ${H_FILES})

target_link_libraries(graphx_sample_cpp
    PRIVATE GraphXLib
    PRIVATE glfw
    PRIVATE cglm
)