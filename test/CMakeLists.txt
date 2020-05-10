#--------------------------------------------------------
#       SET TEST EXECUTABLES
#--------------------------------------------------------
set(UNIT_TESTS unit_tests)

#--------------------------------------------------------
#       SET TEST SOURCES
#--------------------------------------------------------
file(GLOB TESTED_SOURCE_FILES
        "../src/app/localization/LocalizationManager.cpp"
        "../src/app/model/core/AppCore.cpp"
        "../src/app/model/core/ModelConstants.cpp"
        "../src/app/model/menu-components/ShopItem.cpp"
        "../src/app/persistence/FileBasedPersistence.cpp"
        "../src/app/persistence/PersistenceManager.cpp"
        )

file(GLOB TEST_SOURCE_FILES
        "libs/XMLHelper/test_XMLHelper.cpp"
        "app/core/TestCore.cpp"
        "app/persistence/test_FileBasedPersistence.cpp"
        "app/persistence/test_PersistenceManager.cpp"
        )

#--------------------------------------------------------
#       TEST ENGINE BUILDING
#--------------------------------------------------------
FetchContent_MakeAvailable(googletest)

#--------------------------------------------------------
#       CONFIGURE BUILDING
#--------------------------------------------------------

add_executable(${UNIT_TESTS} ${TESTED_SOURCE_FILES} ${TEST_SOURCE_FILES})

target_include_directories(${UNIT_TESTS} PUBLIC ${pugixml_SOURCE_DIR}/src)
target_include_directories(${UNIT_TESTS} PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_include_directories(${UNIT_TESTS} PUBLIC ${PROJECT_SOURCE_DIR}/src/app)
target_include_directories(${UNIT_TESTS} PUBLIC ${PROJECT_SOURCE_DIR}/src/libs)

target_link_libraries(${UNIT_TESTS} gtest_main)
target_link_libraries(${UNIT_TESTS} xmlhelper)
target_link_libraries(${UNIT_TESTS} slogger)

#--------------------------------------------------------
#       CONFIGURE TESTS
#--------------------------------------------------------
add_test(NAME ${UNIT_TESTS} COMMAND make ${UNIT_TESTS})
