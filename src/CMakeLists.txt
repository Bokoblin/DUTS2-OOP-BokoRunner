# TODO: SPLIT MODEL & PERSISTENCE FROM VIEW & LOCALIZATION (SEE ENSEIRB SESSION CURRENT CODE - SSH DOWN UNTIL SEPTEMBER)
#----------------------------------------------------------------------------------
#           APP CONFIGURATION
#----------------------------------------------------------------------------------
set(EXECUTABLE_NAME bokorunner)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules/")

#----------------------------------------------------------------------------------
#           EXTERNAL LIBRARIES SOURCES
#----------------------------------------------------------------------------------
set(PUGIXML_LIB
        ${PUGIXML_ROOT}/PUGIXML/pugixml.hpp
        ${PUGIXML_ROOT}/PUGIXML/pugixml.cpp
        )

#----------------------------------------------------------------------------------
#           INTERNAL LIBRARIES SOURCES
#----------------------------------------------------------------------------------
set(LOGGER_LIB
        ${SIMPLE_LOGGER_ROOT}/Logger.h
        ${SIMPLE_LOGGER_ROOT}/Logger.cpp
        )

file(GLOB MDC_SFML_LIB
        ${MDC_SFML_ROOT}/*.h
        ${MDC_SFML_ROOT}/*.cpp
        )

set(XML_HELPER_LIB
        ${XML_HELPER_ROOT}/XMLHelper.h
        ${XML_HELPER_ROOT}/XMLHelper.cpp
        )

#----------------------------------------------------------------------------------
#           APP SOURCE FILES
#----------------------------------------------------------------------------------
set(APP_ROOT "${PROJECT_SOURCE_DIR}/src/app")
file(GLOB_RECURSE SOURCE_FILES
        ${APP_ROOT}/*.h
        ${APP_ROOT}/*.cpp
        )

#----------------------------------------------------------------------------------
#           LIBRARIES BUILDING
#----------------------------------------------------------------------------------
add_library(pugi SHARED ${PUGIXML_LIB})
add_library(slogger SHARED ${LOGGER_LIB})
add_library(xmlhelper SHARED ${XML_HELPER_LIB})
add_library(mdcsfml SHARED ${MDC_SFML_LIB})

#----------------------------------------------------------------------------------
#           DIRECTORIES INCLUSION
#----------------------------------------------------------------------------------
include_directories(${SFML_INCLUDE_DIR})
include_directories(${PUGIXML_ROOT})
include_directories(${PROJECT_SOURCE_DIR}/src)

#----------------------------------------------------------------------------------
#           LIBRARIES AND EXECUTABLE LINKAGE
#----------------------------------------------------------------------------------
#   Dependencies:
#
#   - pugi: Ø
#   - slogger: Ø
#   - xmlhelper: pugi
#   - mdcsfml: SFML, slogger, xmlhelper -- FIXME: remove xmlhelper and slogger dependency (use a wrapper in the app?)
#   - executable: mdscsfml
#----------------------------------------------------------------------------------
FIND_PACKAGE(SFML 2.4 COMPONENTS audio graphics window system REQUIRED)

target_include_directories(mdcsfml PUBLIC ${SFML_INCLUDE_DIR})

target_link_libraries(xmlhelper pugi)
target_link_libraries(mdcsfml ${SFML_LIBRARIES})
target_link_libraries(mdcsfml slogger)
target_link_libraries(mdcsfml xmlhelper)

add_executable(
        ${EXECUTABLE_NAME}
        ${SOURCE_FILES}
)

#target_link_libraries(${EXECUTABLE_NAME} xmlhelper) FIXME: above
target_link_libraries(${EXECUTABLE_NAME} mdcsfml)
