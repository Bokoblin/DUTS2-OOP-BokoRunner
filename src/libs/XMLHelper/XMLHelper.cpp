#include <unistd.h>
#include "XMLHelper.h"

namespace Bokoblin
{
namespace XMLUtils
{

using std::fstream;
using std::string;
using std::ios;

//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * @brief Creates a file with a content.
 * @details Alternatively overwrite an existing file with given content.
 *
 * @param filename the file name
 * @param content the (new) content
 * @return a boolean indicating if file was created
 *
 * @author Arthur
 * @date 02/05/16 - 16/07/18
 */
bool XMLHelper::createXMLFile(const std::string& filename, const std::string& content)
{
    fstream f;
    f.open(filename.c_str(), ios::out);
    if (f.is_open() && !f.fail()) {
        f << content;
        f.close();
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Remove an XML file
 *
 * @param filename the file name
 * @return a boolean indicating if file was removed
 *
 * @author Arthur
 * @date 16/07/18
 */
bool XMLHelper::removeXMLFile(const std::string& filename)
{
    return remove(filename.c_str()) == EXIT_SUCCESS;
}


/**
 * @brief Checks if a file is valid by trying to parse it
 *
 * @param content a string to check
 * @return a boolean indicating if file has its integrity
 *
 * @author Arthur
 * @date 16/07/18
 */
bool XMLHelper::checkXMLStreamIntegrity(std::istream& content)
{
    pugi::xml_document doc;
    return doc.load(content);
}


/**
 * @brief Checks if an XML file exists
 * @warning Does not check if XML is valid
 *
 * @param filename the file name
 * @return a boolean
 *
 * @author Arthur
 * @date 17/07/18
 */
bool XMLHelper::checkXMLFileExistence(const std::string& filename)
{
    return filename.substr(filename.rfind('.') + 1) == "xml"
            && access(filename.c_str(), F_OK) != -1;
}


/**
 * @brief Loads an XML file
 * @details Performs checks while loading the document
 *
 * @param xmlDocumentObject the object to manipulate xml file more easily
 * @param filename the file name
 * @return true on loading success, false otherwise
 *
 * @author Arthur
 * @date 22/01/18 - 15/07/2018
 */
bool XMLHelper::loadXMLFile(pugi::xml_document& xmlDocumentObject, const std::string& filename)
{
    pugi::xml_parse_result loadingResult = xmlDocumentObject.load_file(filename.c_str());
    return loadingResult.status == pugi::status_ok;
}


/**
 * @brief Retrieves a string matching a given label in a given file
 * @details the string must be contained in a line of this style:
 * <string name="label" value="value" /> inside a root 'resources' node
 *
 * @param filename the file name
 * @param label the label to describe the string
 * @return the string if found or the label between brackets: <> otherwise
 *
 * @author Arthur
 * @date 04/01/17 - 25/01/18
 */
string XMLHelper::loadLabeledString(const string& filename, const string& label)
{
    const string default_value = "<" + label + ">";
    pugi::xml_document doc;

    if (XMLHelper::loadXMLFile(doc, filename)) {
        pugi::xml_node resources = doc.child("resources");

        for (pugi::xml_node item: resources.children("string")) {
            if (string(item.attribute("name").value()) == label) {
                return safeRetrieveXMLValue<string>(item.attribute("value"), "", default_value);
            }
        }
    }

    return default_value;
}


/**
 * @brief Safe retrieves an xml value using a regex and a default value. \n
 * @details Specialization of template for booleans.
 *
 * @param attribute the xml attribute containing the value
 * @param regexString the regex to check against
 * @param defaultValue a default value on regex failure
 * @return a boolean
 *
 * @author Arthur
 * @date 26/01/18
 */
template<>
bool XMLHelper::safeRetrieveXMLValue<bool>
        (const pugi::xml_attribute& attribute, const std::string& regexString, const bool& defaultValue)
{
    const std::string result = std::string(attribute.value());
    const std::regex regex(regexString);

    if (regexString.empty() || std::regex_match(result.c_str(), regex)) {
        return attribute.as_bool(defaultValue);
    } else {
        return defaultValue;
    }
}


/**
 * @brief Safe retrieves an xml value using a regex and a default value. \n
 * @details Specialization of template for signed 32-bit integers.
 *
 * @param attribute the xml attribute containing the value
 * @param regexString the regex to check against
 * @param defaultValue a default value on regex failure
 * @return a signed 32-bit integer
 *
 * @author Arthur
 * @date 26/01/18
 */
template<>
int XMLHelper::safeRetrieveXMLValue<int>
        (const pugi::xml_attribute& attribute, const std::string& regexString, const int& defaultValue)
{
    const std::string result = std::string(attribute.value());
    const std::regex regex(regexString);

    if (regexString.empty() || std::regex_match(result.c_str(), regex)) {
        return attribute.as_int(defaultValue);
    } else {
        return defaultValue;
    }
}


/**
 * @brief Safe retrieves an xml value using a regex and a default value. \n
 * @details Specialization of template for strings.
 *
 * @param attribute the xml attribute containing the value
 * @param regexString the regex to check against
 * @param defaultValue a default value on regex failure
 * @return a string
 *
 * @author Arthur
 * @date 26/01/18
 */
template<>
string XMLHelper::safeRetrieveXMLValue<string>
        (const pugi::xml_attribute& attribute, const std::string& regexString, const string& defaultValue)
{
    const std::string result = std::string(attribute.value());
    const std::regex regex(regexString);

    if (regexString.empty() || std::regex_match(result.c_str(), regex)) {
        return attribute.as_string(defaultValue.c_str());
    } else {
        return defaultValue;
    }
}


/**
 * @brief Safe retrieves an xml value using a regex and a default value. \n
 * @details Specialization of template for unsigned 32-bit integers.
 *
 * @param attribute the xml attribute containing the value
 * @param regexString the regex to check against
 * @param defaultValue a default value on regex failure
 * @return an unsigned 32-bit integer
 *
 * @author Arthur
 * @date 26/01/18
 */
template<>
unsigned int XMLHelper::safeRetrieveXMLValue<unsigned int>
        (const pugi::xml_attribute& attribute, const std::string& regexString, const unsigned int& defaultValue)
{
    const std::string result = std::string(attribute.value());
    const std::regex regex(regexString);

    if (regexString.empty() || std::regex_match(result.c_str(), regex)) {
        return attribute.as_uint(defaultValue);
    } else {
        return defaultValue;
    }
}

} //namespace XMLUtils
} //namespace Bokoblin
