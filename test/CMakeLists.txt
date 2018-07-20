if (ENABLE_TESTS)

#--------------------------------------------------------
#       SET TEST EXECUTABLES
#--------------------------------------------------------
set(UNIT_TESTS unit_tests)

#--------------------------------------------------------
#       SET TEST SOURCES
#--------------------------------------------------------
file(GLOB TEST_SOURCE_FILES
        "libs/XMLHelper/test_XMLHelper.cpp"
        )

#----------------------------------------------------------------------------------
#           EXTERNAL LIBRARIES SOURCES
#----------------------------------------------------------------------------------
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules/")

set(PUGIXML_LIB
        ${PUGIXML_ROOT}/PUGIXML/pugixml.hpp
        ${PUGIXML_ROOT}/PUGIXML/pugixml.cpp
        )

#----------------------------------------------------------------------------------
#           INTERNAL LIBRARIES SOURCES
#----------------------------------------------------------------------------------
set(LOGGER_LIB
        ../src/libs/Logger/Logger.h
        ../src/libs/Logger/Logger.cpp
        )

set(XML_HELPER_LIB
        ${XML_HELPER_ROOT}/XMLHelper.h
        ${XML_HELPER_ROOT}/XMLHelper.cpp
        )

#--------------------------------------------------------
#       TEST ENGINE BUILDING
#--------------------------------------------------------
add_subdirectory(../ext-libs/googletest-1.8.0 ${CMAKE_BINARY_DIR}/googletest/googletest-download)


#--------------------------------------------------------
#       LIBRARIES BUILDING #FIXME: Don't know if needed for those already "shared"
#--------------------------------------------------------

add_library(gtest_pugi SHARED ${PUGIXML_LIB})
add_library(gtest_xmlhelper SHARED ${XML_HELPER_LIB})

#--------------------------------------------------------
#       CONFIGURE BUILDING
#--------------------------------------------------------

target_link_libraries(gtest_xmlhelper gtest_pugi)

add_executable(${UNIT_TESTS} ${TEST_SOURCE_FILES})

target_include_directories(gtest_xmlhelper PUBLIC ${PUGIXML_ROOT})
target_include_directories(${UNIT_TESTS} PUBLIC ${PUGIXML_ROOT})
target_include_directories(${UNIT_TESTS} PUBLIC ${PROJECT_SOURCE_DIR}/src/app)
target_include_directories(${UNIT_TESTS} PUBLIC ${PROJECT_SOURCE_DIR}/src/libs)

target_link_libraries(${UNIT_TESTS} gtest_main)
target_link_libraries(${UNIT_TESTS} gtest_xmlhelper)

#--------------------------------------------------------
#       CONFIGURE TESTS
#--------------------------------------------------------
add_test(NAME ${UNIT_TESTS} COMMAND make ${UNIT_TESTS})

enable_testing()

endif ()
