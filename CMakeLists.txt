cmake_minimum_required(VERSION 3.10)
project (Openexif VERSION 2.1.4)


# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)

include(CMakeDependentOption)
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

set(OPENEXIF_MAJOR_VESION 2)
set(OPENEXIF_MINOR_VERSION 1)
set(OPENEXIF_PATCH_VERSION 4)
set(OPENEXIF_VERSION ${OPENEXIF_MAJOR_VESION}.${OPENEXIF_MINOR_VERSION}.${OPENEXIF_PATCH_VERSION})

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules")

set(CMAKE_INSTALL_PREFIX "/opt/openexif-2.1.4")

list(APPEND CMAKE_PREFIX_PATH "/opt")


option(BUILD_TESTS "Enable building tests" ON)

add_subdirectory(src)

if(${BUILD_TESTS})
    message(STATUS "Building tests.")
    add_subdirectory(test)
endif()

if(${BUILD_EXAMPLES})
    message(STATUS "Building examples.")
    add_subdirectory(examples)
endif()


# Generate and install package configuration files
configure_package_config_file(
    ${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in 
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION 
        ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
install(
    EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}:: 
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# Create package version configuration file
write_basic_package_version_file(
    "${PROJECT_NAME}ConfigVersion.cmake"
    COMPATIBILITY   SameMajorVersion
)

# Install package configuration files 
install(
    FILES 
        ${CMAKE_CURRENT_BINARY_DIR}/OpenexifConfig.cmake 
        ${CMAKE_CURRENT_BINARY_DIR}/OpenexifConfigVersion.cmake 
    DESTINATION 
        ${CMAKE_INSTALL_LIBDIR}/cmake/Openexif
)