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


#--------------------------------------------------------
#       TEST ENGINE BUILDING
#--------------------------------------------------------
add_subdirectory(../ext-libs/googletest-1.8.0 ${CMAKE_BINARY_DIR}/googletest/googletest-download)


#--------------------------------------------------------
#       CONFIGURE BUILDING
#--------------------------------------------------------

add_executable(${UNIT_TESTS} ${TEST_SOURCE_FILES})

target_include_directories(${UNIT_TESTS} PUBLIC ${PUGIXML_ROOT})
target_include_directories(${UNIT_TESTS} PUBLIC ${PROJECT_SOURCE_DIR}/src/app)
target_include_directories(${UNIT_TESTS} PUBLIC ${PROJECT_SOURCE_DIR}/src/libs)

target_link_libraries(${UNIT_TESTS} gtest_main)
target_link_libraries(${UNIT_TESTS} xmlhelper)

#--------------------------------------------------------
#       CONFIGURE TESTS
#--------------------------------------------------------
add_test(NAME ${UNIT_TESTS} COMMAND make ${UNIT_TESTS})

enable_testing()

endif ()
