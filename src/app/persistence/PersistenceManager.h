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

#ifndef PERSISTENCE_MANAGER_H
#define PERSISTENCE_MANAGER_H

#include <set>
#include <fstream>
#include "libs/Logger/Logger.h"
#include "libs/XMLHelper/XMLHelper.h"
#include "app/model/core/AppCore.h"
#include "app/model/core/ModelConstants.h"
#include "app/persistence/PersistenceException.h"

class AppCore;

//TODO: Unit tests before commit

/**
 * The PersistenceManager class manages the app persistence. \n
 * The persistence method is abstracted from app's point of view in order to easily change
 * persistence system by only changing this file. \n
 * The current persistence system uses an xml config file.
 *
 * @author Arthur
 * @date 27/01/18 - 17/07/18
 */
class PersistenceManager
{
public:
    //=== METHODS
    static void initContext(AppCore* appCore);
    static void closeContext();
    static void checkContext();
    static void initPersistence();
    static void fetchConfiguration();
    static void fetchStatistics();
    static void fetchLeaderboard();
    static void fetchActivatedBonus();
    static void updatePersistence(); //TODO: global + split versions
    static void resetPersistence();
    static void deletePersistence(); //TODO: use in CLI to clean the persistence

private:
    //=== METHODS
    static bool createConfigFile();
    static bool checkStreamIntegrity(std::istream& stream);
    static bool checkStreamIntegrityFromConfigFile();
    static bool checkStreamIntegrityFromXMLDocument();
    static bool fetchConfigurationFromConfigFile();
    static bool fetchStatisticsFromConfigFile();
    static bool fetchActivatedBonusFromConfigFile();
    static bool fetchLeaderboardFromConfigFile();
    static bool persistConfigurationToConfigFile();

    //=== ATTRIBUTES
    static bool m_isInit;
    static AppCore* m_appCore;
    static pugi::xml_document m_doc;
};

#endif
