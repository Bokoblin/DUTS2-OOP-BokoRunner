cmake_minimum_required(VERSION 2.8)

#Configuration du projet
set(PROJECT_NAME runner)
project(${PROJECT_NAME})
set(EXECUTABLE_NAME ${PROJECT_NAME})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#include libraries
set(SFML_ROOT "${PROJECT_SOURCE_DIR}/ext-libs/SFML-2.4.2")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules/")

set(PUGIXML_ROOT "${PROJECT_SOURCE_DIR}/ext-libs/pugixml-1.8/src")
set(PUGIXML_LIB
        ${PUGIXML_ROOT}/PUGIXML/pugixml.hpp
        ${PUGIXML_ROOT}/PUGIXML/pugixml.cpp
        )

set(LOGGER_LIB
        src/libs/Logger/Logger.h
        src/libs/Logger/Logger.cpp
        )

file(GLOB MDC-SFML_LIB
        "src/libs/MDC-SFML/src/*.h"
        "src/libs/MDC-SFML/src/*.cpp"
        )


set(XML_HELPER_LIB
        src/libs/XMLHelper/XMLHelper.h
        src/libs/XMLHelper/XMLHelper.cpp
        )


file(GLOB_RECURSE SOURCE_FILES
        "src/app/*.h"
        "src/app/*.cpp"
        )

add_library(PUGIXML ${PUGIXML_LIB})

add_executable(
        ${EXECUTABLE_NAME}
        ${PUGIXML_LIB}
        ${LOGGER_LIB}
        ${XML_HELPER_LIB}
        ${MDC-SFML_LIB}
        ${SOURCE_FILES}
)

FIND_PACKAGE(SFML 2.4 COMPONENTS audio graphics window system REQUIRED)

include_directories(${PUGIXML_ROOT})
include_directories(${SFML_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/src)
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})