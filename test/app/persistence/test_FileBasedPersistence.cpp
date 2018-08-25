#include <fstream>
#include <gtest/gtest.h>
#include <persistence/FileBasedPersistence.h>
#include "../core/TestCore.h"

namespace
{

/**
 * This test class performs tests on the app class FileBasedPersistence
 */
class FileBasedPersistenceTest: public ::testing::Test {
protected:
    TestCore* testCore{};


    void SetUp() override
    {
        testCore = new TestCore();
        FileBasedPersistence::setAppCore(testCore);
    }

    void TearDown() override
    {
        XMLHelper::removeXMLFile(testCore->getConfigFile());
        delete testCore;
    }
};

/**
 * Tests on FileBasedPersistence::createConfigFile() function
 */
TEST_F(FileBasedPersistenceTest, createConfigFile)
{
    ASSERT_FALSE(XMLHelper::checkXMLFileExistence(testCore->getConfigFile()));
    ASSERT_TRUE(FileBasedPersistence::createConfigFile());
    ASSERT_TRUE(XMLHelper::checkXMLFileExistence(testCore->getConfigFile()));
}

/**
 * Tests on FileBasedPersistence::loadConfigFile() function if existing
 */
TEST_F(FileBasedPersistenceTest, loadConfigFileExisting)
{
    FileBasedPersistence::createConfigFile();
    ASSERT_TRUE(FileBasedPersistence::loadConfigFile());
}

/**
 * Tests on FileBasedPersistence::loadConfigFile() function if not existing
 */
TEST_F(FileBasedPersistenceTest, loadConfigFileNonExisting)
{
    ASSERT_FALSE(FileBasedPersistence::loadConfigFile());
}

/**
 * Tests on FileBasedPersistence::removeConfigFile() function on existing file
 */
TEST_F(FileBasedPersistenceTest, removeConfigFileExisting)
{
    FileBasedPersistence::createConfigFile();
    ASSERT_TRUE(FileBasedPersistence::removeConfigFile());
}

/**
 * Tests on FileBasedPersistence::removeConfigFile() function on non existing file
 */
TEST_F(FileBasedPersistenceTest, removeConfigFileNotExisting)
{
    ASSERT_FALSE(FileBasedPersistence::removeConfigFile());
}

/**
 * Tests on FileBasedPersistence::checkStreamIntegrity() function on empty stream
 */
TEST_F(FileBasedPersistenceTest, checkEmptyStreamIntegrity)
{
    std::fstream f;
    ASSERT_FALSE(FileBasedPersistence::checkStreamIntegrity(f));
}

/**
 * Tests on FileBasedPersistence::checkStreamIntegrity() function on filled stream with valid content
 */
TEST_F(FileBasedPersistenceTest, checkStreamIntegrity)
{
    std::stringstream ss;
    ss << DEFAULT_CONFIG_CONTENT.c_str();
    ASSERT_TRUE(FileBasedPersistence::checkStreamIntegrity(ss));
}

/**
 * Tests on FileBasedPersistence::checkStreamIntegrity() function on filled stream with invalid content
 */
TEST_F(FileBasedPersistenceTest, checkStreamIntegrityInvalid)
{
    std::stringstream ss;
    ss << TEST_CONFIG_FILE.c_str();
    ASSERT_FALSE(FileBasedPersistence::checkStreamIntegrity(ss));
}

/**
 * Tests on FileBasedPersistence::checkStreamIntegrityFromConfigFile() function on non existing file
 */
TEST_F(FileBasedPersistenceTest, checkStreamIntegrityFromNonExistingConfigFile)
{
    ASSERT_FALSE(FileBasedPersistence::checkStreamIntegrityFromConfigFile());
}

/**
 * Tests on FileBasedPersistence::checkStreamIntegrityFromConfigFile() function on existing file
 */
TEST_F(FileBasedPersistenceTest, checkStreamIntegrityFromExistingConfigFile)
{
    FileBasedPersistence::createConfigFile();
    ASSERT_TRUE(FileBasedPersistence::checkStreamIntegrityFromConfigFile());
}

/**
 * Tests on FileBasedPersistence::checkStreamIntegrityFromXMLDocument() function on non existing file
 */
TEST_F(FileBasedPersistenceTest, checkStreamIntegrityFromEmptyXMLDocument)
{
    ASSERT_FALSE(FileBasedPersistence::checkStreamIntegrityFromXMLDocument());
}

/**
 * Tests on FileBasedPersistence::checkStreamIntegrityFromXMLDocument() function on existing file
 */
TEST_F(FileBasedPersistenceTest, checkStreamIntegrityFromXMLDocument)
{
    FileBasedPersistence::createConfigFile();
    FileBasedPersistence::loadConfigFile();
    ASSERT_TRUE(FileBasedPersistence::checkStreamIntegrityFromXMLDocument());
}

/**
 * Tests on FileBasedPersistence::fetchConfigurationFromConfigFile() function
 */
TEST_F(FileBasedPersistenceTest, fetchConfigurationFromConfigFile)
{
    FileBasedPersistence::createConfigFile();
    FileBasedPersistence::loadConfigFile();
    ASSERT_TRUE(FileBasedPersistence::fetchConfigurationFromConfigFile());
}

/**
 * Tests on FileBasedPersistence::fetchStatisticsFromConfigFile() function
 */
TEST_F(FileBasedPersistenceTest, fetchStatisticsFromConfigFile)
{
    FileBasedPersistence::createConfigFile();
    FileBasedPersistence::loadConfigFile();
    ASSERT_TRUE(FileBasedPersistence::fetchStatisticsFromConfigFile());
}

/**
 * Tests on FileBasedPersistence::fetchActivatedBonusFromConfigFile() function
 */
TEST_F(FileBasedPersistenceTest, fetchActivatedBonusFromConfigFile)
{
    FileBasedPersistence::createConfigFile();
    FileBasedPersistence::loadConfigFile();
    ASSERT_TRUE(FileBasedPersistence::fetchActivatedBonusFromConfigFile());
}

/**
 * Tests on FileBasedPersistence::fetchLeaderboardFromConfigFile() function
 */
TEST_F(FileBasedPersistenceTest, fetchLeaderboardFromConfigFile)
{
    FileBasedPersistence::createConfigFile();
    FileBasedPersistence::loadConfigFile();
    ASSERT_TRUE(FileBasedPersistence::fetchLeaderboardFromConfigFile());
}

/**
 * Tests on FileBasedPersistence::persistConfigurationToConfigFile() function
 */
TEST_F(FileBasedPersistenceTest, persistConfigurationToConfigFile)
{
    ASSERT_TRUE(FileBasedPersistence::persistConfigurationToConfigFile());
}

} // namespace gtest
