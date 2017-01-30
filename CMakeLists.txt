cmake_minimum_required(VERSION 3.2)

#Configuration du projet
set(PROJECT_NAME runner)
project(${PROJECT_NAME})
set(EXECUTABLE_NAME ${PROJECT_NAME})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#include libraries
set(SFML_ROOT "${PROJECT_SOURCE_DIR}/libs/SFML-2.3.2")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${SFML_ROOT}/cmake/Modules/")

file(GLOB SOURCE_FILES
        "src/model/*.h"
        "src/model/*.cpp"
        "src/view/*.h"
        "src/view/*.cpp"
        "src/constants.h"
        "src/main.cpp"
        )

set(PUGI_LIB
        libs/pugixml-1.8/src/pugixml.hpp
        libs/pugixml-1.8/src/pugixml.cpp
        )

add_executable(runner ${PUGI_LIB} ${SOURCE_FILES})

FIND_PACKAGE(SFML 2 COMPONENTS system window graphics audio REQUIRED)

include_directories( ${SFML_INCLUDE_DIR} )
target_link_libraries( ${EXECUTABLE_NAME} ${SFML_LIBRARIES})