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

#include <app/model/models/SplashScreenModel.h>
#include <app/model/models/MenuModel.h>
#include <app/model/models/GameModel.h>

using Bokoblin::SimpleLogger::Logger;

static const int SCENE_WIDTH = 900;
static const int SCENE_HEIGHT = 600;

/**
 * Initializes the application and controls its loop
 *
 * @author Arthur, Florian
 * @date 21/02/16 - 12/10/18
 */
int main() //TODO: Complete CLI app (maybe a App class can work differently if ENABLE_UI is set in order to only have one main)
{
    //=== Initialize app data and text

    AppCore appCore;
    Logger::setLoggerFile("./boko_runner.log");
    PersistenceManager::initContext(&appCore);
    PersistenceManager::fetchConfiguration();
    PersistenceManager::fetchStatistics();
    PersistenceManager::fetchLeaderboard();

    //=== Initialize app state, and event object

    appCore.setAppState(SPLASH);

    //=== Program loop

    while (appCore.getAppState() != QUIT) {
        if (appCore.getAppState() == SPLASH) {
            SplashScreenModel splashModel(&appCore);

            while (appCore.getAppState() == SPLASH) {
                splashModel.nextStep();
                appCore.setAppState(MENU);
            }
        }
        if (appCore.getAppState() == MENU) {
            MenuModel menuModel(&appCore);

            while (appCore.getAppState() == MENU) {
                menuModel.nextStep();
                appCore.setAppState(GAME);
            }
        }
        if (appCore.getAppState() == GAME) {
            GameModel gameModel(SCENE_WIDTH, SCENE_HEIGHT, &appCore);

            while (appCore.getAppState() == GAME) {
                gameModel.nextStep();
                appCore.setAppState(QUIT);
            }
        }
        if (appCore.getAppState() == QUIT) {
            PersistenceManager::updatePersistence();
        }
    }

    PersistenceManager::closeContext();
    LocalizationManager::closeContext();

    return EXIT_SUCCESS;
}
