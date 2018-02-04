/* Copyright 2018 Jolivet Arthur & Laronze Florian

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef XML_PERSISTENCE_HELPER_H
#define XML_PERSISTENCE_HELPER_H

#include <fstream>
#include <regex>
#include "PUGIXML/pugixml.hpp"
#include "libs/Logger/Logger.h"

/**
 * The XMLHelper class provides high-level methods
 * to work with an xml file handler object in order to read or write in the file.
 * It abstracts PugiXML usage from other classes visibility
 *
 * @author Arthur
 * @date 22/01/18 - 04/02/18
 */
class XMLHelper
{
public:
    //=== METHODS
    static void createXMLFile(const std::string &filename, const std::string &content);
    static bool checkXMLFileIntegrity(const std::string &filename);
    static bool loadXMLFile(pugi::xml_document &xmlDocumentObject, const std::string &filename);
    static std::string loadLabeledString(const std::string &filename, const std::string &label);

    /**
     * Safe retrieves an xml value using a regex and a default value. \n
     *
     * This function supports, through specialization, the following types :
     * strings, booleans, signed and unsigned integers. \n
     *
     * It is strongly advised to use an integer for enumeration.
     * Passing other types than the above listed may lead into an undefined behaviour. \n
     *
     * You can specify an empty regex, the check won't be taken in account.
     * You MUST specify a valid default value, otherwise you can encounter
     * an undefined behaviour on retrieval failure.
     *
     * @param attribute the xml attribute containing the value
     * @param regexString the regex to check against
     * @param defaultValue a default value on regex failure
     * @return a Type object
     *
     * @author Arthur
     * @date 25/01/18 - 26/01/18
     */
    template <typename Type> static Type safeRetrieveXMLValue(const pugi::xml_attribute &attribute,
                                                              const std::string &regexString, const Type &defaultValue)
    {
        //Implementation must be in-place due to C++ limitation

        const std::string result = std::string(attribute.value());
        const std::regex regex(regexString);

        if (regexString.empty() || std::regex_match(result.c_str(), regex))
        {
            std::istringstream ss(result);
            Type res;
            ss >> res;
            return res;
        }
        else
        {
            return defaultValue;
        }
    }
};

template<> bool XMLHelper::safeRetrieveXMLValue<bool>
        (const pugi::xml_attribute &attribute, const std::string &regexString, const bool &defaultValue);

template<> int XMLHelper::safeRetrieveXMLValue<int>
        (const pugi::xml_attribute &attribute, const std::string &regexString, const int &defaultValue);

template<> std::string XMLHelper::safeRetrieveXMLValue<std::string>
        (const pugi::xml_attribute &attribute, const std::string &regexString, const std::string &defaultValue);

template<> unsigned int XMLHelper::safeRetrieveXMLValue<unsigned int>
        (const pugi::xml_attribute &attribute, const std::string &regexString, const unsigned int &defaultValue);

#endif
