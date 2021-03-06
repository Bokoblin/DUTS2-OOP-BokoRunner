#include <gtest/gtest.h>
#include <persistence/PersistenceException.h>
#include "persistence/PersistenceManager.h"
#include "../core/TestCore.h"

using Bokoblin::XMLUtils::XMLHelper;

namespace
{

/**
 * The test class PersistenceManagerTest
 * performs tests on the app class PersistenceManager
 *
 * @author Arthur
 * @date 25/08/18 - 14/01/19
 *
 * @see PersistenceManager
 */
class PersistenceManagerTest: public ::testing::Test
{
protected:
    TestCore testCore;

    void TearDown() override
    {
        PersistenceManager::closeContext();
        XMLHelper::removeXMLFile(testCore.getPersistenceContext());
    }
};

/**
 * Tests on PersistenceManager::initContext() function
 */
TEST_F(PersistenceManagerTest, initContext)
{
    ASSERT_FALSE(PersistenceManager::isInit());
    PersistenceManager::initContext(testCore);
    ASSERT_TRUE(PersistenceManager::isInit());
}

/**
 * Tests on PersistenceManager::closeContext() function
 */
TEST_F(PersistenceManagerTest, closeContext)
{
    ASSERT_FALSE(PersistenceManager::isInit());
    PersistenceManager::closeContext();
    ASSERT_FALSE(PersistenceManager::isInit());

    PersistenceManager::initContext(testCore);

    ASSERT_TRUE(PersistenceManager::isInit());
    PersistenceManager::closeContext();
    ASSERT_FALSE(PersistenceManager::isInit());
}

/**
 * Tests on PersistenceManager::checkContext() function without initialization
 */
TEST_F(PersistenceManagerTest, checkUninitializedContext)
{
    try {
        PersistenceManager::checkContext();
        FAIL();
    } catch (const PersistenceException& e) {
    }
}

/**
 * Tests on PersistenceManager::checkContext() function after initialization
 */
TEST_F(PersistenceManagerTest, checkInitializedContext)
{
    try {
        PersistenceManager::initContext(testCore);
        PersistenceManager::checkContext();
        PersistenceManager::closeContext();
    } catch (const PersistenceException& e) {
        FAIL();
    }
}

/**
 * Tests on PersistenceManager::initPersistence() function
 */
TEST_F(PersistenceManagerTest, initPersistence)
{
    ASSERT_FALSE(XMLHelper::checkXMLFileExistence(testCore.getPersistenceContext()));
    PersistenceManager::initContext(testCore);
    ASSERT_TRUE(XMLHelper::checkXMLFileExistence(testCore.getPersistenceContext()));
    PersistenceManager::initPersistence();
    ASSERT_TRUE(XMLHelper::checkXMLFileExistence(testCore.getPersistenceContext()));
}

/**
 * Tests on PersistenceManager::updatePersistence() function if existing
 */
TEST_F(PersistenceManagerTest, updateExistingPersistence)
{
    PersistenceManager::initContext(testCore);
    ASSERT_TRUE(XMLHelper::checkXMLFileExistence(testCore.getPersistenceContext()));
    PersistenceManager::updatePersistence();
    ASSERT_TRUE(XMLHelper::checkXMLFileExistence(testCore.getPersistenceContext()));
}

/**
 * Tests on PersistenceManager::updatePersistence() function if not existing
 */
TEST_F(PersistenceManagerTest, updateNonExistingPersistence)
{
    ASSERT_FALSE(XMLHelper::checkXMLFileExistence(testCore.getPersistenceContext()));
    PersistenceManager::updatePersistence();
    ASSERT_FALSE(XMLHelper::checkXMLFileExistence(testCore.getPersistenceContext()));
}

/**
 * Tests on PersistenceManager::resetPersistence() function
 */
TEST_F(PersistenceManagerTest, resetPersistence)
{
    ASSERT_FALSE(XMLHelper::checkXMLFileExistence(testCore.getPersistenceContext()));
    PersistenceManager::initContext(testCore);
    ASSERT_TRUE(XMLHelper::checkXMLFileExistence(testCore.getPersistenceContext()));
    PersistenceManager::resetPersistence();
    ASSERT_TRUE(XMLHelper::checkXMLFileExistence(testCore.getPersistenceContext()));
}

/**
 * Tests on PersistenceManager::deletePersistence() function
 */
TEST_F(PersistenceManagerTest, deletePersistence)
{
    ASSERT_FALSE(XMLHelper::checkXMLFileExistence(testCore.getPersistenceContext()));
    PersistenceManager::initContext(testCore);
    ASSERT_TRUE(XMLHelper::checkXMLFileExistence(testCore.getPersistenceContext()));
    PersistenceManager::deletePersistence();
    ASSERT_FALSE(XMLHelper::checkXMLFileExistence(testCore.getPersistenceContext()));
}

} // namespace gtest
