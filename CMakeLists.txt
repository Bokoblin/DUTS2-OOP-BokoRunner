cmake_minimum_required(VERSION 2.8)

#--------------------------------------------------------
#           PROJECT CONFIGURATION
#--------------------------------------------------------
set(PROJECT_NAME DUTS2-POO-ProjetRunner)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
project(${PROJECT_NAME})

option(ENABLE_TESTS "Enable unit tests"     ON)
option(ENABLE_UI    "Enable user interface" ON) #In case your device can't support provided SFML

#----------------------------------------------------------------------------------
#           EXTERNAL LIBRARIES ROOT DIRECTORY CONFIGURATION
#----------------------------------------------------------------------------------
set(EXTERNAL_LIBS_ROOT "${PROJECT_SOURCE_DIR}/ext-libs")
set(SFML_ROOT "${EXTERNAL_LIBS_ROOT}/SFML-2.4.2")
set(PUGIXML_ROOT "${EXTERNAL_LIBS_ROOT}/pugixml-1.8/src")

#----------------------------------------------------------------------------------
#           INTERNAL LIBRARIES ROOT DIRECTORY CONFIGURATION
#----------------------------------------------------------------------------------
set(INTERNAL_LIBS_ROOT "${PROJECT_SOURCE_DIR}/src/libs")
set(SIMPLE_LOGGER_ROOT "${INTERNAL_LIBS_ROOT}/Logger")
set(MDC_SFML_ROOT "${INTERNAL_LIBS_ROOT}/MDC-SFML/src")
set(XML_HELPER_ROOT "${INTERNAL_LIBS_ROOT}/XMLHelper")

#--------------------------------------------------------
#       SUBDIRS ADDING
#--------------------------------------------------------

add_subdirectory(src)
add_subdirectory(test)
