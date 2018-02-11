#include "XMLHelper.h"

using std::fstream;
using std::string;
using std::ios;
using Bokoblin::SimpleLogger::Logger;

//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Creates a file with a content.
 * Alternatively overwrite an existing file with given content.
 *
 * @param filename the file name
 * @param content the (new) content
 *
 * @author Arthur
 * @date 02/05/16 - 22/01/18
 */
void XMLHelper::createXMLFile(const std::string &filename, const std::string &content)
{
    fstream f;
    f.open(filename.c_str(), ios::out);
    f << content;
    f.close();
}


/**
 * Checks if a file is valid and has not been corrupted
 *
 * Structure checking is already done by PugiXML when loading the file
 *
 * @return a boolean indicating if file has its integrity
 *
 * @author Arthur
 * @date ??
 */
bool XMLHelper::checkXMLFileIntegrity(const std::string &filename)
{
    fstream f;
    string line;

    f.open(filename.c_str(), ios::in);

    //=== Opening test
    if (f.fail())
        return false;


    //=== Integrity test

    //TODO : integrity check (content)


    return true;
}


/**
 * Loads an XML file
 *
 * @param xmlDocumentObject the object to manipulate xml file more easily
 * @param filename the file name
 * @return true on loading success, false otherwise
 *
 * @author Arthur
 * @date 22/01/18
 */
bool XMLHelper::loadXMLFile(pugi::xml_document &xmlDocumentObject, const std::string &filename)
{
    pugi::xml_parse_result loadingResult = xmlDocumentObject.load_file(filename.c_str());

    if (loadingResult.status == pugi::status_ok)
    {
        Logger::printInfoOnConsole("File \"" + filename + "\" loading success");
        return true;
    }
    else
    {
        Logger::printErrorOnConsole("File \"" + filename + "\" loading failure");
        return false;
    }
}


/**
 * Retrieves a string matching a given label in a given file
 *
 * @param filename the file name
 * @param label the label to describe the string
 * @return the string if found or the label in brackets otherwise
 *
 * @author Arthur
 * @date 04/01/17 - 25/01/18
 */
string XMLHelper::loadLabeledString(const string &filename, const string &label)
{
    const string default_value = "<" + label + ">";
    pugi::xml_document doc;

    if (XMLHelper::loadXMLFile(doc, filename))
    {
        pugi::xml_node resources = doc.child("resources");

        for (pugi::xml_node item: resources.children("string"))
        {
            if (string(item.attribute("name").value()) == label) {
                return safeRetrieveXMLValue<string>(item.attribute("value"), "", default_value);
            }
        }
        Logger::printWarningOnConsole("No string was found for expression \"" + label
                + "\" in the file \"" + filename +"\"");
    }

    return default_value;
}


/**
 * Safe retrieves an xml value using a regex and a default value. \n
 * Specialization of template for booleans.
 *
 * @param attribute the xml attribute containing the value
 * @param regexString the regex to check against
 * @param defaultValue a default value on regex failure
 * @return a boolean
 *
 * @author Arthur
 * @date 26/01/18
 */
template<> bool XMLHelper::safeRetrieveXMLValue<bool>
        (const pugi::xml_attribute &attribute, const std::string &regexString, const bool &defaultValue)
{
    const std::string result = std::string(attribute.value());
    const std::regex regex(regexString);

    if (regexString.empty() || std::regex_match(result.c_str(), regex))
        return attribute.as_bool(defaultValue);
    else
        return defaultValue;
}


/**
 * Safe retrieves an xml value using a regex and a default value. \n
 * Specialization of template for signed 32-bit integers.
 *
 * @param attribute the xml attribute containing the value
 * @param regexString the regex to check against
 * @param defaultValue a default value on regex failure
 * @return a signed 32-bit integer
 *
 * @author Arthur
 * @date 26/01/18
 */
template<> int XMLHelper::safeRetrieveXMLValue<int>
        (const pugi::xml_attribute &attribute, const std::string &regexString, const int &defaultValue)
{
    const std::string result = std::string(attribute.value());
    const std::regex regex(regexString);

    if (regexString.empty() || std::regex_match(result.c_str(), regex))
        return attribute.as_int(defaultValue);
    else
        return defaultValue;
}


/**
 * Safe retrieves an xml value using a regex and a default value. \n
 * Specialization of template for strings.
 *
 * @param attribute the xml attribute containing the value
 * @param regexString the regex to check against
 * @param defaultValue a default value on regex failure
 * @return a string
 *
 * @author Arthur
 * @date 26/01/18
 */
template<> string XMLHelper::safeRetrieveXMLValue<string>
        (const pugi::xml_attribute &attribute, const std::string &regexString, const string &defaultValue)
{
    const std::string result = std::string(attribute.value());
    const std::regex regex(regexString);

    if (regexString.empty() || std::regex_match(result.c_str(), regex))
        return attribute.as_string(defaultValue.c_str());
    else
        return defaultValue;
}


/**
 * Safe retrieves an xml value using a regex and a default value. \n
 * Specialization of template for unsigned 32-bit integers.
 *
 * @param attribute the xml attribute containing the value
 * @param regexString the regex to check against
 * @param defaultValue a default value on regex failure
 * @return an unsigned 32-bit integer
 *
 * @author Arthur
 * @date 26/01/18
 */
template<> unsigned int XMLHelper::safeRetrieveXMLValue<unsigned int>
        (const pugi::xml_attribute &attribute, const std::string &regexString, const unsigned int &defaultValue)
{
    const std::string result = std::string(attribute.value());
    const std::regex regex(regexString);

    if (regexString.empty() || std::regex_match(result.c_str(), regex))
        return attribute.as_uint(defaultValue);
    else
        return defaultValue;
}
