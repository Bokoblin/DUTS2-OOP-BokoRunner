/* Copyright 2018 Jolivet Arthur

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

#ifndef FILE_BASED_PERSISTENCE_H
#define FILE_BASED_PERSISTENCE_H

#include <set>
#include <fstream>
#include "libs/Logger/Logger.h"
#include "libs/XMLHelper/XMLHelper.h"
#include "app/model/core/AppCore.h"
#include "app/model/core/ModelConstants.h"

class AppCore;

/**
 * The FileBasedPersistence class contains the logic for a file-based persistence. \n
 * It is designed to be used only by the PersistenceManager class. \n
 * This persistence uses an xml config file.
 *
 * @author Arthur
 * @date 25/08/18 - 25/09/18
 */
class FileBasedPersistence
{
public:
    //=== METHODS
    static bool createConfigFile();
    static bool loadConfigFile();
    static bool removeConfigFile();
    static bool checkStreamIntegrity(std::istream& stream);
    static bool checkStreamIntegrityFromConfigFile();
    static bool checkStreamIntegrityFromXMLDocument();
    static bool fetchConfigurationFromConfigFile();
    static bool fetchStatisticsFromConfigFile();
    static bool fetchActivatedBonusFromConfigFile();
    static bool fetchLeaderboardFromConfigFile();
    static bool persistConfigurationToConfigFile();

    //=== GETTERS / SETTERS
    static AppCore* getAppCore();
    static void setAppCore(AppCore* appCore); //NOTE: MUST BE CALLED AT LEAST ONCE BEFORE USING OTHER FUNCTIONS

private:
    //=== METHODS
    static void nullSafeGuard();
    static void insertScore(std::set<int>& array, const pugi::xml_node& scoreItem);
    static void saveScores(const std::set<int>& array, const pugi::xml_node& scoreNode);

    //=== ATTRIBUTES
    static AppCore* m_appCore;
    static pugi::xml_document m_doc;
};

#endif
