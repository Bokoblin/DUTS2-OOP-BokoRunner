#----------------------------------------------------------------------------------
#           INTERNAL LIBRARIES SOURCES
#----------------------------------------------------------------------------------
set(LOGGER_LIB
        ${SIMPLE_LOGGER_ROOT}/Logger.h
        ${SIMPLE_LOGGER_ROOT}/Logger.cpp
        )

file(GLOB_RECURSE MDC_SFML_LIB
        ${MDSF_SRC_ROOT}/*.h
        ${MDSF_SRC_ROOT}/*.cpp
        ${MDSF_SRC_ROOT}/*/*.h
        ${MDSF_SRC_ROOT}/*/*.cpp
        ${MDSF_SRC_ROOT}/*/*/*.h
        ${MDSF_SRC_ROOT}/*/*/*.cpp
        )

set(XML_HELPER_LIB
        ${XML_HELPER_ROOT}/XMLHelper.h
        ${XML_HELPER_ROOT}/XMLHelper.cpp
        )

#----------------------------------------------------------------------------------
#           APP SOURCE FILES
#----------------------------------------------------------------------------------
set(APP_ROOT "${PROJECT_SOURCE_DIR}/src/app")

if (ENABLE_UI)
    file(GLOB_RECURSE SOURCE_FILES
            ${APP_ROOT}/*/*.h
            ${APP_ROOT}/*/*.cpp
            ${APP_ROOT}/main.cpp
            )
else ()
    file(GLOB_RECURSE SOURCE_FILES
            ${APP_ROOT}/localization/*.h
            ${APP_ROOT}/localization/*.cpp
            ${APP_ROOT}/model/*.h
            ${APP_ROOT}/model/*.cpp
            ${APP_ROOT}/persistence/*.h
            ${APP_ROOT}/persistence/*.cpp
            ${APP_ROOT}/main_cli.cpp
            )
endif ()

#----------------------------------------------------------------------------------
#           LIBRARIES BUILDING
#----------------------------------------------------------------------------------
add_library(slogger SHARED ${LOGGER_LIB})
add_library(xmlhelper SHARED ${XML_HELPER_LIB})
if (ENABLE_UI)
    add_library(mdcsfml STATIC ${MDC_SFML_LIB})
endif ()

#----------------------------------------------------------------------------------
#           COMPILE DEFINITIONS
#----------------------------------------------------------------------------------
if (ENABLE_FILE_LOG)
    target_compile_definitions(slogger PUBLIC ENABLE_FILE_LOGGING=1)
endif ()

#----------------------------------------------------------------------------------
#           LIBRARIES AND EXECUTABLE LINKAGE
#----------------------------------------------------------------------------------
#   Dependency Tree
#
#   bokorunner
#   |__ mdcsfml [ENABLE_UI only]
#   |   |__ sfml
#   |__ xmlhelper
#   |   |__ pugixml
#   |__ slogger
#----------------------------------------------------------------------------------
FetchContent_MakeAvailable(pugixml)
target_include_directories(xmlhelper PUBLIC ${pugixml_SOURCE_DIR}/src)
target_link_libraries(xmlhelper pugixml)

add_executable(bokorunner ${SOURCE_FILES})
target_include_directories(bokorunner PUBLIC ${PROJECT_SOURCE_DIR}/src)

if (ENABLE_UI)
    FetchContent_MakeAvailable(sfml)

    target_include_directories(mdcsfml PUBLIC ${sfml_SOURCE_DIR}/include)
    target_include_directories(mdcsfml PUBLIC ${sfml_BINARY_DIR}/lib)
    target_compile_definitions(mdcsfml PUBLIC MDSF_RES_ROOT="${INTERNAL_LIBS_ROOT}/MDC-SFML/res")

    target_link_libraries(mdcsfml sfml-audio sfml-graphics sfml-system sfml-window)
    target_link_libraries(bokorunner mdcsfml xmlhelper slogger)
else ()
    target_link_libraries(bokorunner xmlhelper slogger)
endif ()
