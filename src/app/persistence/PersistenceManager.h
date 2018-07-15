﻿/* Copyright 2018 Jolivet Arthur

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

//TODO: maybe store config as static document xml instead of loading file each time
//TODO: Try to reduce file size by factorising what is possible

/**
 * The PersistenceManager class manages the app persistence. \n
 * The persistence method is abstracted from app's point of view in order to easily change
 * persistence system by only changing this file. \n
 * The current persistence system uses an xml config file.
 *
 * @author Arthur
 * @date 27/01/18 - 11/02/18
 */
class PersistenceManager
{
public:
    //=== METHODS
    static void initContext(AppCore *appCore);
    static void closeContext();
    static void checkContext();
    static void initPersistence();
    static void fetchConfiguration();
    static void fetchLeaderboard();
    static void fetchActivatedBonus();
    static void updatePersistence(); //TODO: global + split versions
    static void deletePersistence();

private:
    //=== METHODS
    static void createConfigFile();
    static bool checkConfigFileIntegrity();
    static bool fetchConfigurationFromConfigFile();
    static bool fetchActivatedBonusFromConfigFile();
    static bool fetchLeaderboardFromConfigFile();
    static bool persistConfigurationToConfigFile();

    //=== ATTRIBUTES
    static bool m_isInit;
    static AppCore *m_appCore;
};

#endif