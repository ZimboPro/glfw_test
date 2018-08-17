cmake_minimum_required (VERSION 3.0)

project(og)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

include(FetchContent)

FetchContent_Declare(
    glfw
    URL "https://github.com/glfw/glfw/releases/download/3.2.1/glfw-3.2.1.zip"
)

FetchContent_GetProperties(glfw)

if(NOT glfw_POPULATED)
  FetchContent_Populate(glfw)
  add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG origin/c
)

FetchContent_GetProperties(glad)

if(NOT glad_POPULATED)
  FetchContent_Populate(glad)
endif()

FetchContent_Declare(
    std_image
    GIT_REPOSITORY https://github.com/jschmidt42/stb-cmake.git
)

FetchContent_GetProperties(std_image)

if(NOT std_image_POPULATED)
  FetchContent_Populate(std_image)
endif()

include_directories(${glad_SOURCE_DIR}/include ${glfw_SOURCE_DIR}/include ${std_image_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/include)

add_executable(og
    src/Functions.cpp
    src/main.cpp
    src/Shaders.cpp
    ${glad_SOURCE_DIR}/src/glad.c
)

target_link_libraries(og glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(og ${OPENGL_gl_LIBRARY})

if (OPENGL_GLU_FOUND)
    target_link_libraries(og ${OPENGL_glu_LIBRARY})
endif()