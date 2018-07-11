cmake_minimum_required (VERSION 3.0)

project(og)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -fPIC -framework Cocoa -framework IOKit -framework CoreFoundation -framework CoreVideo")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(SOURCE 
    src/Functions.cpp
    src/main.cpp)

add_executable(og
    ${SOURCE}
)

include(ExternalProject)

set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/libogd)

ExternalProject_Add(libogsrc
  URL "https://github.com/glfw/glfw/releases/download/3.2.1/glfw-3.2.1.zip"
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION} -DBUILD_SHARED_LIBS=OFF
)

include_directories(${EXTERNAL_INSTALL_LOCATION})
include_directories(${EXTERNAL_INSTALL_LOCATION}/include)

add_dependencies(og libogsrc)

#target_link_libraries(og ${EXTERNAL_INSTALL_LOCATION}/lib/libglfw.dylib)
target_link_libraries(og ${EXTERNAL_INSTALL_LOCATION}/lib/libglfw3.a)
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    #target_include_directories(og ${OPENGL_INCLUDE_DIR})
    target_link_libraries(og ${OPENGL_gl_LIBRARY})
endif()

if (OPENGL_GLU_FOUND)
    target_link_libraries(og ${OPENGL_glu_LIBRARY})
endif()