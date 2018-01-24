#include "XMLPersistenceHelper.h"

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
void XMLPersistenceHelper::createXMLFile(const std::string &filename, const std::string &content)
{
    fstream f;
    f.open(filename.c_str(), ios::out);
    f << content;
    f.close();
}


/**
 * Checks if a file is valid and has not been corrupted
 *
 * @return a boolean indicating if file has its integrity
 *
 * @author Arthur
 * @date ??
 */
bool XMLPersistenceHelper::checkFileIntegrity(const std::string &filename)
{
    fstream f;
    string line;

    f.open(filename.c_str(), ios::in);

    //=== Opening test
    if (f.fail())
        return false;

    //=== Validity test

    //TODO : validity check (structure)


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
bool XMLPersistenceHelper::loadFile(pugi::xml_document &xmlDocumentObject, const std::string &filename)
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
string XMLPersistenceHelper::loadLabeledString(const string &filename, const string &label)
{
    pugi::xml_document doc;
    if (XMLPersistenceHelper::loadFile(doc, filename))
    {
        pugi::xml_node resources = doc.child("resources");

        for (pugi::xml_node item: resources.children("string"))
        {
            if (string(item.attribute("name").value()) == label) {
                return item.attribute("value").value();
            }
        }
        Logger::printWarningOnConsole("No string was find for expression \"" + label
                + "\" in the file \"" + filename +"\"");
    }

    return "<" + label + ">";
}

