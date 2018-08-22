cmake_minimum_required (VERSION 3.0)

project(og)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

set(FETCHCONTENT_QUIET OFF)

include(FetchContent)

FetchContent_Declare(
    glfw
    
    URL "https://github.com/glfw/glfw/releases/download/3.2.1/glfw-3.2.1.zip"
)

FetchContent_GetProperties(glfw)

if(NOT glfw_POPULATED)
  FetchContent_Populate(glfw)
  set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
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

FetchContent_Declare(
    glm
    URL https://github.com/g-truc/glm/archive/0.9.7.0.zip
)

FetchContent_GetProperties(glm)

if(NOT glm_POPULATED)
  FetchContent_Populate(glm)
endif()

FetchContent_Declare(
    assimp
    URL https://github.com/assimp/assimp/archive/master.zip
)

FetchContent_GetProperties(assimp)

if(NOT assimp_POPULATED)
  FetchContent_Populate(assimp)
  set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
  set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)

  add_subdirectory(${assimp_SOURCE_DIR} ${assimp_BINARY_DIR})
endif()

include_directories(
    ${glad_SOURCE_DIR}/include 
    ${glfw_SOURCE_DIR}/include 
    ${std_image_SOURCE_DIR} 
    ${glm_SOURCE_DIR} 
    ${assimp_SOURCE_DIR}/include

    ${CMAKE_SOURCE_DIR}/include
)

add_executable(
    og

    src/Functions.cpp
    src/main.cpp
    src/Shaders.cpp
    src/TextureImages.cpp
    src/Camera.cpp
    src/Mesh.cpp
    src/Models.cpp

    ${glad_SOURCE_DIR}/src/glad.c
)

target_link_libraries(og glfw assimp)

find_package(OpenGL REQUIRED)
target_link_libraries(og ${OPENGL_gl_LIBRARY})

if (OPENGL_GLU_FOUND)
    target_link_libraries(og ${OPENGL_glu_LIBRARY})
endif()