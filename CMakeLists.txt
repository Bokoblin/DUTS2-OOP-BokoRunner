cmake_minimum_required(VERSION 2.8)

#Configuration du projet
set(PROJECT_NAME runner)
project(${PROJECT_NAME})
set(EXECUTABLE_NAME ${PROJECT_NAME})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#include libraries
set(SFML_ROOT "${PROJECT_SOURCE_DIR}/ext-libs/SFML-2.4.2")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules/")

set(PUGI_LIB
        ext-libs/pugixml-1.8/src/pugixml.hpp
        ext-libs/pugixml-1.8/src/pugixml.cpp
        )

set(LOGGER_LIB
        src/libs/Logger/Logger.h
        src/libs/Logger/Logger.cpp
        )

file(GLOB MDC-SFML_LIB
        "src/libs/MDC-SFML/src/*.h"
        "src/libs/MDC-SFML/src/*.cpp"
        )

file(GLOB_RECURSE SOURCE_FILES
        "src/app/*.h"
        "src/app/*.cpp"
        )


add_executable(${EXECUTABLE_NAME} ${PUGI_LIB} ${LOGGER_LIB} ${MDC-SFML_LIB} ${SOURCE_FILES})

FIND_PACKAGE(SFML 2.4 COMPONENTS audio graphics window system REQUIRED)

include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})