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

#include <iostream>
#include <fstream>
#include "../../../ext-libs/pugixml-1.8/src/pugixml.hpp"
#include "../Logger/Logger.h"

/**
 * The XMLPersistenceHelper class provides high-level methods
 * to work with an xml file handler object in order to read or write in the file
 *
 * @author Arthur
 * @date 22/01/18 - 23/01/18
 */
class XMLPersistenceHelper
{
public:

    //=== METHODS
    static void createXMLFile(const std::string &filename, const std::string &content);
    static bool checkFileIntegrity(const std::string &filename);
    static bool loadFile(pugi::xml_document &xmlDocumentObject, const std::string &filename);
    static std::string loadLabeledString(const std::string &filename, const std::string &label);
};

#endif
