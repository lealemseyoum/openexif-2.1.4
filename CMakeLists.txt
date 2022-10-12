cmake_minimum_required(VERSION 3.10)
project (Openexif VERSION 2.1.4)


# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)

include(CMakeDependentOption)
include(GNUInstallDirs)

set(OPENEXIF_MAJOR_VESION 2)
set(OPENEXIF_MINOR_VERSION 1)
set(OPENEXIF_PATCH_VERSION 4)
set(OPENEXIF_VERSION ${OPENEXIF_MAJOR_VESION}.${OPENEXIF_MINOR_VERSION}.${OPENEXIF_PATCH_VERSION})

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules")

set(CMAKE_INSTALL_PREFIX "/opt/openexif-2.1.4")

list(APPEND CMAKE_PREFIX_PATH "/opt")


option(BUILD_TESTS "Enable building tests" OFF)

add_subdirectory(src)

if(${BUILD_TESTS})
    message(STATUS "Building tests.")
    add_subdirectory(test)
endif()

if(${BUILD_EXAMPLES})
    message(STATUS "Building examples.")
    add_subdirectory(examples)
endif()