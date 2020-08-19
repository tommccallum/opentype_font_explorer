cmake_minimum_required(VERSION 3.5)
project(OpenType)

## CMAKE_SOURCE_DIR=/home/tom/Development/OpenType
## CMAKE_BINARY_DIR=/home/tom/Development/OpenType/build
## PROJECT_SOURCE_DIR=/home/tom/Development/OpenType
## PROJECT_BINARY_DIR=/home/tom/Development/OpenType/build
message("CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}")
message("CMAKE_BINARY_DIR=${CMAKE_BINARY_DIR}")
message("PROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR}")
message("PROJECT_BINARY_DIR=${PROJECT_BINARY_DIR}")
message("CMAKE_PROJECT_NAME=${CMAKE_PROJECT_NAME}")

## CMAKE_MODULE_PATH is where CMAKE modules can be loaded
## it is blank by default.
## It is used by include() and find_package()
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})

## set version for this project
set(${CMAKE_PROJECT_NAME}_VERSION_MAJOR 0)
set(${CMAKE_PROJECT_NAME}_VERSION_MINOR 1)
message("${CMAKE_PROJECT_NAME}_VERSION_MAJOR=${${CMAKE_PROJECT_NAME}_VERSION_MAJOR}")
message("${CMAKE_PROJECT_NAME}_VERSION_MINOR=${${CMAKE_PROJECT_NAME}_VERSION_MINOR}")

## set files which just need copying over in final build
set(COPYABLE
    LICENSE.txt
    README.md)

## provide option for user to turn off build tests, on by default
## option(name description initial_value)
option(INSTALL_TEST "Install to local directory instead of system" ON)
option(LIB_TYPE "Static or shared lib type" STATIC)

if( INSTALL_TEST )
    set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install)
endif()
message("CMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}")

## copies over config.h.in to config.h replacing
## CMakeList variables within the file
configure_file(
     "${PROJECT_SOURCE_DIR}/src/config.h.in"
     "${PROJECT_BINARY_DIR}/config.h"
)


## add the directories we will use for include files
include_directories("${CMAKE_SOURCE_DIR}/include")
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")

message("== BUILD PHASE")

foreach(src ${COPYABLE})
    ## the @ONLY tells it to only replace variables of the form @VAR@
    configure_file(${CMAKE_SOURCE_DIR}/${src} ${CMAKE_BINARY_DIR}/${src} @ONLY)
endforeach()

## build the library
add_subdirectory(src)
## build the dependent executables
add_subdirectory(executables)

message("== POST BUILD PHASE")
include(CTest)
message("BUILD_TESTING=${BUILD_TESTING}")

## only if build tests are required do we bring in catch
add_subdirectory(tests)
