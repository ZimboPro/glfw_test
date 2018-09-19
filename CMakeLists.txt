cmake_minimum_required (VERSION 3.11)

project(graphics)

set(FETCHCONTENT_QUIET OFF)

include(FetchContent)

# Glad
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG origin/c
)

FetchContent_GetProperties(glad)

if(NOT glad_POPULATED)
  FetchContent_Populate(glad)
endif()

# GLFW
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

# SFML
FetchContent_Declare(
    sfml
    URL https://www.sfml-dev.org/files/SFML-2.5.0-sources.zip
)

FetchContent_GetProperties(sfml)

if(NOT sfml_POPULATED)
  FetchContent_Populate(sfml)
  set(SFML_BUILD_WINDOW OFF CACHE BOOL "" FORCE)
  set(SFML_BUILD_GRAPHICS OFF CACHE BOOL "" FORCE)
  set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
  add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR})
endif()

# STB_Image
FetchContent_Declare(
    std_image
    GIT_REPOSITORY https://github.com/jschmidt42/stb-cmake.git
)

FetchContent_GetProperties(std_image)

if(NOT std_image_POPULATED)
  FetchContent_Populate(std_image)
endif()

# GLM
FetchContent_Declare(
    glm
    URL https://github.com/g-truc/glm/archive/0.9.7.0.zip
)

FetchContent_GetProperties(glm)

if(NOT glm_POPULATED)
  FetchContent_Populate(glm)
endif()

# Freetype2
FetchContent_Declare(
    freetype2
    URL https://download.savannah.gnu.org/releases/freetype/freetype-2.9.1.tar.gz
)

FetchContent_GetProperties(freetype2)

if(NOT freetype2)
  FetchContent_Populate(freetype2)
  add_subdirectory(${freetype2_SOURCE_DIR} ${freetype2_BINARY_DIR})
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

if (APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif(APPLE)

# Assimp
FetchContent_Declare(
    assimp
    URL https://github.com/assimp/assimp/archive/master.zip
)

FetchContent_GetProperties(assimp)

if(NOT assimp_POPULATED)
  FetchContent_Populate(assimp)
  set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
  set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
  set(ASSIMP_NO_EXPORT ON CACHE BOOL "" FORCE)
  set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
  set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)
  set(ASSIMP_BUILD_OBJ_IMPORTER ON CACHE BOOL "" FORCE)

  add_subdirectory(${assimp_SOURCE_DIR} ${assimp_BINARY_DIR})
endif()

#ffmpeg
set(VIDEO FALSE)
if (VIDEO)

    FetchContent_Declare(
        ffmpeg
        if (APPLE)
            URL https://ffmpeg.zeranoe.com/builds/macos64/static/ffmpeg-20180913-1b98bfb-macos64-static.zip
        elseif(UNIX AND NOT APPLE)
            URL https://johnvansickle.com/ffmpeg/releases/ffmpeg-release-64bit-static.tar.xz
        else()
            URL https://ffmpeg.zeranoe.com/builds/win64/static/ffmpeg-20180913-1b98bfb-win64-static.zip
        endif()
    )

    FetchContent_GetProperties(ffmpeg)

    if(NOT ffmpeg_POPULATED)
        add_subdirectory(${ffmpeg_SOURCE_DIR})
    endif()

endif()


# library
add_library(
    graphics
    
    src/Shaders.cpp
    src/TextureImages.cpp
    src/Camera.cpp
    src/Mesh.cpp
    src/Model_Texture.cpp
    src/Model_Sprite.cpp
    src/ModelGroup.cpp
    src/Font3d.cpp
    src/Log.cpp
    src/Text.cpp
    src/SpriteRender.cpp
    src/Window.cpp
    src/Juicy.cpp

    ${glad_SOURCE_DIR}/src/glad.c
)


find_package(OpenGL REQUIRED)

if (OPENGL_GLU_FOUND)
    target_link_libraries(graphics PUBLIC ${OPENGL_glu_LIBRARY})
endif()

target_include_directories(graphics PUBLIC 
    ${glad_SOURCE_DIR}/include 
    ${glfw_SOURCE_DIR}/include
    ${sfml_SOURCE_DIR}/include 
    ${std_image_SOURCE_DIR} 
    ${glm_SOURCE_DIR} 
    ${assimp_SOURCE_DIR}/include
    ${freetype2_SOURCE_DIR}/include

    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(graphics PUBLIC glfw assimp freetype sfml-audio sfml-system ${OPENGL_gl_LIBRARY})

# install
install(TARGETS graphics DESTINATION ${CMAKE_BINARY_DIR}/Graphics)
set(INSTALL_DIR)

# CPack
set(CPACK_GENERATOR "OSXX11" CACHE STRING "" FORCE)
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Leslie" CACHE STRING "" FORCE)
set(CPACK_PACKAGE_NAME "graphics" CACHE STRING "" FORCE)
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_INSTALL_DIRECTORY ${CMAKE_BINARY_DIR} CACHE PATH "" FORCE)

include(CPack)

# add_executable(
#     og
#     src/main.cpp
#     src/Functions.cpp
# )

# target_link_libraries(og graphics)
