cmake_minimum_required(VERSION 2.6)
project(CG184)

message(STATUS "CG184_SOURCE_DIR : " ${CG184_SOURCE_DIR})

#-------------------------------------------------------------------------------
# CMake modules
#-------------------------------------------------------------------------------
list(APPEND CMAKE_MODULE_PATH "${CG184_SOURCE_DIR}/cmake/modules/")

#-------------------------------------------------------------------------------
# CG184 paths
#-------------------------------------------------------------------------------
set(CG184_INCLUDE_DIRS "${CG184_SOURCE_DIR}/CG184/include")


##################
# Build on Linux #
##################
set(LINUX UNIX AND NOT APPLE)
if(UNIX)

    # GCC configuration
    if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")

        set(GCC_CXX_FLAGS "-std=gnu++11 -m64")

        message(STATUS "0")
        # X11 Dependencies
        set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lXi")
        set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lXxf86vm")
        set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lXinerama")
        set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lXcursor")
        set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lXfixes")
        set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lXrandr")
        set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lXext")
        set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lXrender")
        set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lX11")
        set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lpthread")
        set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lxcb")
        set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lXau")

        # Debug configuration
        if(BUILD_DEBUG)
            set(CMAKE_BUILD_TYPE Debug)
        else(BUILD_DEBUG)
            set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -O3")
            set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -fopenmp")
        endif(BUILD_DEBUG)

        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_CXX_FLAGS}")

    endif()

    # Clang configuration (experimental)
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")

        set(CLANG_CXX_FLAGS "-std=c++11 -m64")

        if(BUILD_DEBUG)
            set(CMAKE_BUILD_TYPE Debug)
        else(BUILD_DEBUG)
            set(CLANG_CXX_FLAGS "${CLANG_CXX_FLAGS} -O3")
            set(CLANG_CXX_FLAGS "${CLANG_CXX_FLAGS} -funroll-loops")
            set(CLANG_CXX_FLAGS "${CLANG_CXX_FLAGS} -Wno-narrowing")
            set(CLANG_CXX_FLAGS "${CLANG_CXX_FLAGS} -Wno-deprecated-register")
        endif(BUILD_DEBUG)

        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CLANG_CXX_FLAGS}")

    endif()

endif(UNIX)

####################
# Build on Windows #
####################
if(WIN32)

    if(MSVC)

        set(MSVC_CXX_FLAGS "-std=gnu++11")
        set(CMAKE_BUILD_TYPE Debug)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MSVC_CXX_FLAGS}")

    endif(MSVC)

    if(MINGW)

        set(MSVC_CXX_FLAGS "-std=gnu++11")
        set(CMAKE_BUILD_TYPE Debug)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MSVC_CXX_FLAGS}")

    endif(MINGW)

endif(WIN32)

#-------------------------------------------------------------------------------
# Find dependencies
#-------------------------------------------------------------------------------

# Required packages
find_package(OpenGL REQUIRED)

# Use pkg-config for GLEW & GLFW if available
find_package(PkgConfig QUIET)

# GLEW
if(PKGCONFIG_FOUND)
    pkg_search_module(GLEW QUIET glew32)
else(PKGCONFIG_FOUND)
    find_package(GLEW QUIET)
endif()

if(NOT GLEW_FOUND)
    include_directories("${CG184_SOURCE_DIR}/deps/glew/include")
    set(GLEW_LIBRARY_DIRS "${CG184_SOURCE_DIR}/deps/glew/lib")
endif()

message(STATUS "GLEW_LIBRARIES : " ${GLEW_LIBRARIES})

# GLFW
if(PKGCONFIG_FOUND)
    pkg_search_module(GLFW QUIET glfw3)
else(PKGCONFIG_FOUND)
    find_package(GLFW QUIET)
endif()
if(NOT GLFW_FOUND)
    add_subdirectory("${CG184_SOURCE_DIR}/deps/glfw")
	include_directories("${CG184_SOURCE_DIR}/deps/glfw/include")
    set_property( TARGET glfw APPEND_STRING PROPERTY COMPILE_FLAGS -w )
endif()

# ASSIMP
find_package(ASSIMP QUIET)
if(NOT ASSIMP_FOUND)
    include_directories("${CG184_SOURCE_DIR}/deps/Assimp/include")
    set(ASSIMP_LIBRARY_DIRS "${CG184_SOURCE_DIR}/deps/Assimp/lib")
endif()
message(STATUS "Found ASSIMP in ${ASSIMP_INCLUDE_DIR}")

# stb_image
include_directories("${CG184_SOURCE_DIR}/deps/Extras")

#-------------------------------------------------------------------------------
# Set include directories
#-------------------------------------------------------------------------------
include_directories(
        ${CG184_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${GLFW_INCLUDE_DIRS}
)

#-------------------------------------------------------------------------------
# Set link directories
#-------------------------------------------------------------------------------
link_directories(
        ${GLEW_LIBRARY_DIRS}
        ${GLFW_LIBRARY_DIRS}
		${ASSIMP_LIBRARY_DIRS}
)

#-------------------------------------------------------------------------------
# Set Resources directories
#-------------------------------------------------------------------------------
set(RESOURCES_DIR "${CG184_SOURCE_DIR}/Resources")
set(SHADER_DIR "${CG184_SOURCE_DIR}/TestShaders")

set(RESOURCE_FILE ${RESOURCES_DIR}/objects/rock/cubeEdit.obj)

#-------------------------------------------------------------------------------
# Add subdirectories
#-------------------------------------------------------------------------------

# HelloGL library source directory
add_subdirectory("CG184")


#-------------------------------------------------------------------------------
# Packing
#-------------------------------------------------------------------------------

# Install settings
set(CMAKE_INSTALL_PREFIX "${CG184_SOURCE_DIR}")
