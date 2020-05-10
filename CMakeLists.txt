cmake_minimum_required(VERSION 3.11...3.14)
include(FetchContent)
include(cmake/compatibility.cmake)

#--------------------------------------------------------
#           PROJECT CONFIGURATION
#--------------------------------------------------------
project(DUTS2-OOP-ProjetRunner
        VERSION 2.0
        DESCRIPTION "University Technical Institute, Sem. 2 - OOP Project : Auto-scrolling runner game"
        LANGUAGES CXX)
option(ENABLE_TESTS "Enable unit tests" OFF)
option(ENABLE_UI "Enable user interface" ON) #In case your device can't support provided SFML
option(ENABLE_FILE_LOG "Enable logging to a file, default is stdout" OFF)

#----------------------------------------------------------------------------------
#           CXX CONFIGURATION
#----------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -Wextra")

#----------------------------------------------------------------------------------
#           EXTERNAL DEPENDENCIES DECLARATION
#----------------------------------------------------------------------------------
FetchContent_Declare(
        googletest
        GIT_REPOSITORY  https://github.com/google/googletest.git
        GIT_TAG         release-1.8.1
)
FetchContent_Declare(
        pugixml
        GIT_REPOSITORY  https://github.com/zeux/pugixml.git
        GIT_TAG         v1.10
)
FetchContent_Declare(
        sfml
        GIT_REPOSITORY  https://github.com/sfml/sfml.git
        GIT_TAG         2.5.1
)

#----------------------------------------------------------------------------------
#           INTERNAL LIBRARIES ROOT DIRECTORY CONFIGURATION
#----------------------------------------------------------------------------------
set(INTERNAL_LIBS_ROOT "${PROJECT_SOURCE_DIR}/src/libs")
set(SIMPLE_LOGGER_ROOT "${INTERNAL_LIBS_ROOT}/Logger")
set(MDSF_SRC_ROOT "${INTERNAL_LIBS_ROOT}/MDC-SFML/src")
set(XML_HELPER_ROOT "${INTERNAL_LIBS_ROOT}/XMLHelper")

#--------------------------------------------------------
#       SUBDIRS ADDING
#--------------------------------------------------------

add_subdirectory(src)

if (ENABLE_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(test)
endif ()