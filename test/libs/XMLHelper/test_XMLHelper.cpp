#include <gtest/gtest.h>
#include <model/core/ModelConstants.h>
#include "XMLHelper/XMLHelper.h"

namespace
{

/**
 * This test class performs tests on the class XMLHelper
 * from the library XMLHelper
 */
class XMLHelperTest: public ::testing::Test {
protected:

    const std::string filename = "test.xml";
    const std::string validContent = R"(<?xml version="1.0"?><node></node>)";

    void TearDown() override
    {
        remove(filename.c_str());
    }
};

/**
 * Tests on XMLHelper::createXMLFile() function
 */
TEST_F(XMLHelperTest, createXMLFile)
{
    ASSERT_FALSE(access(filename.c_str(), F_OK) != -1);
    XMLHelper::createXMLFile(filename, "");
    ASSERT_TRUE(access(filename.c_str(), F_OK) != -1);
}

/**
 * Tests on XMLHelper::removeXMLFile() function
 */
TEST_F(XMLHelperTest, removeXMLFile)
{
    XMLHelper::createXMLFile(filename, "");
    ASSERT_TRUE(access(filename.c_str(), F_OK) != -1);
    XMLHelper::removeXMLFile(filename);
    ASSERT_FALSE(access(filename.c_str(), F_OK) != -1);
}

/**
 * Tests on XMLHelper::checkXMLFileExistence() function
 */
TEST_F(XMLHelperTest, checkXMLFileExistence)
{
    ASSERT_FALSE(XMLHelper::checkXMLFileExistence(filename));
    XMLHelper::createXMLFile(filename, "");
    ASSERT_TRUE(XMLHelper::checkXMLFileExistence(filename));
}

/**
 * Tests on XMLHelper::checkXMLStreamIntegrity() function
 */
TEST_F(XMLHelperTest, checkXMLStreamIntegrity)
{
    std::stringstream stream;
    stream << "";
    ASSERT_FALSE(XMLHelper::checkXMLStreamIntegrity(stream));
    stream << "egergegegeq";
    ASSERT_FALSE(XMLHelper::checkXMLStreamIntegrity(stream));
    stream << validContent.c_str();
    ASSERT_TRUE(XMLHelper::checkXMLStreamIntegrity(stream));
    stream << "<?xml version=\"1.0\"?";
    ASSERT_FALSE(XMLHelper::checkXMLStreamIntegrity(stream));
    stream << DEFAULT_CONFIG_CONTENT.c_str();
    ASSERT_TRUE(XMLHelper::checkXMLStreamIntegrity(stream));
}

/**
 * Tests on XMLHelper::loadXMLFile() function
 */
TEST_F(XMLHelperTest, loadXMLFile)
{
    pugi::xml_document document;
    ASSERT_FALSE(XMLHelper::loadXMLFile(document, filename));
    XMLHelper::createXMLFile(filename, "azdzdzd");
    ASSERT_FALSE(XMLHelper::loadXMLFile(document, filename));
    XMLHelper::createXMLFile(filename, validContent);
    ASSERT_TRUE(XMLHelper::loadXMLFile(document, filename));
}

/**
 * Tests on XMLHelper::loadLabeledString() function
 */
TEST_F(XMLHelperTest, loadLabeledString)
{
    const std::string label = "test";
    const std::string bracketLabel = "<test>";

    ASSERT_EQ(XMLHelper::loadLabeledString(filename, label), bracketLabel);
    XMLHelper::createXMLFile(filename, "azdzdzd");
    ASSERT_EQ(XMLHelper::loadLabeledString(filename, label), bracketLabel);
    XMLHelper::createXMLFile(filename, validContent);
    ASSERT_EQ(XMLHelper::loadLabeledString(filename, label), bracketLabel);
    XMLHelper::createXMLFile(filename, R"(<string name="label" value="value" />)");
    ASSERT_EQ(XMLHelper::loadLabeledString(filename, label), bracketLabel);
    XMLHelper::createXMLFile(filename, R"(<?xml version="1.0"?><string name="label" value="value" />)");
    ASSERT_EQ(XMLHelper::loadLabeledString(filename, label), bracketLabel);
    XMLHelper::createXMLFile(filename, R"(<?xml version="1.0"?><resources><string name="test" value="value" /></resources>)");
    ASSERT_EQ(XMLHelper::loadLabeledString(filename, label), "value");
}

} // namespace gtest
