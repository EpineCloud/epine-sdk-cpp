cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
PROJECT(epine-sdk
    VERSION 1.0.0
)

option(BUILD_SHARED_LIBS "Build the shared library" OFF)
option(BUILD_UNIT_TESTS "Builds unit tests target" OFF)

set(MAJOR 1)
set(MINOR 6)
set(PATCH 0)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(DEFAULT_BUILD_TYPE "Release")
    message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src ALL_SRC)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src/Auth ALL_SRC)

file(GLOB ALL_HEADERS ${CMAKE_CURRENT_LIST_DIR}/src/*.h)

add_library(epine-sdk ${ALL_SRC})

# Link sioclient
set(sioclient_location ${CMAKE_CURRENT_LIST_DIR}/lib/sio/lib/libsioclient.a)
find_library(sioclient_location NAMES libsioclient.a)
add_library(sioclient STATIC IMPORTED)
set_target_properties(sioclient PROPERTIES IMPORTED_LOCATION ${sioclient_location})
target_link_libraries(epine-sdk sioclient)

target_include_directories(epine-sdk
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src
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

if (CMAKE_VERSION VERSION_GREATER "3.1")
set_property(TARGET epine-sdk PROPERTY CXX_STANDARD 11)
set_property(TARGET epine-sdk PROPERTY CXX_STANDARD_REQUIRED ON)
else()
set_property(TARGET epine-sdk APPEND_STRING PROPERTY COMPILE_FLAGS "-std=c++11")
endif()
if(BUILD_SHARED_LIBS)
set_target_properties(epine-sdk
	PROPERTIES
		SOVERSION ${MAJOR}
		VERSION ${MAJOR}.${MINOR}.${PATCH}
	)
endif()
list(APPEND TARGET_LIBRARIES epine-sdk)

include(GNUInstallDirs)

install(FILES ${ALL_HEADERS} 
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(TARGETS ${TARGET_LIBRARIES}
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

if(BUILD_UNIT_TESTS)
message(STATUS "Building with unit test support.")
enable_testing()
add_subdirectory(test)
endif()
