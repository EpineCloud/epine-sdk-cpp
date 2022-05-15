# Requirements
cmake_minimum_required(VERSION 3.4 FATAL_ERROR)

# Metadata
PROJECT(epine-sdk
    VERSION 1.0.0
)
set(MAJOR 1)
set(MINOR 0)
set(PATCH 0)

# Options
option(BUILD_SHARED_LIBS "Build the shared library" OFF)
option(BUILD_UNIT_TESTS "Builds unit tests target" OFF)

# Default build type
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(DEFAULT_BUILD_TYPE "Release")
    message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Add all source directories to ALL_SRC
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src ALL_SRC)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src/Constants ALL_SRC)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src/Config ALL_SRC)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src/Auth ALL_SRC)

# Add headers to ALL_HEADERS
file(GLOB ALL_HEADERS ${CMAKE_CURRENT_LIST_DIR}/src/*.h)

# Add library "epine-sdk" for compilation
add_library(epine-sdk ${ALL_SRC})

# Link "sioclient" library to "epine-sdk" (!!!maybe not cross platform!!!)
set(sioclient_location ${CMAKE_CURRENT_LIST_DIR}/lib/sio/lib/libsioclient.a)
find_library(sioclient_location NAMES libsioclient.a)
add_library(sioclient STATIC IMPORTED)
set_target_properties(sioclient PROPERTIES IMPORTED_LOCATION ${sioclient_location})
target_link_libraries(epine-sdk sioclient)

# Include dirs into library compilation
target_include_directories(epine-sdk
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src
        ${CMAKE_CURRENT_LIST_DIR}/src/Constants
        ${CMAKE_CURRENT_LIST_DIR}/src/Config
        ${CMAKE_CURRENT_LIST_DIR}/src/Auth
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/lib/sio/lib/rapidjson/include
        ${CMAKE_CURRENT_LIST_DIR}/lib/sio/include
        ${CMAKE_CURRENT_LIST_DIR}/lib/http/include
)
target_link_directories(epine-sdk
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/lib/sio/lib
)

# Set C++11 depending on cmake verision
if (CMAKE_VERSION VERSION_GREATER "3.1")
    set_property(TARGET epine-sdk PROPERTY CXX_STANDARD 11)
    set_property(TARGET epine-sdk PROPERTY CXX_STANDARD_REQUIRED ON)
else()
    set_property(TARGET epine-sdk APPEND_STRING PROPERTY COMPILE_FLAGS "-std=c++11")
endif()

# Build shared libs
if(BUILD_SHARED_LIBS)
    set_target_properties(epine-sdk
        PROPERTIES
            SOVERSION ${MAJOR}
            VERSION ${MAJOR}.${MINOR}.${PATCH}
        )
endif()

# Append "epine-sdk" to TARGET_LIBRARIES
list(APPEND TARGET_LIBRARIES epine-sdk)

# Add GNU standard installation directories
include(GNUInstallDirs)

# Install files
install(FILES ${ALL_HEADERS} 
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install targets
install(TARGETS ${TARGET_LIBRARIES}
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Build unit tests
if(BUILD_UNIT_TESTS)
    message(STATUS "Building with unit test support.")
    enable_testing()
    add_subdirectory(test)
endif()
