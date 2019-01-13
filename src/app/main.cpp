/* Copyright 2016-2019 Jolivet Arthur & Laronze Florian

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

#include "app/view/utils/ViewConstants.h"
#include "app/view/views/SplashScreenView.h"
#include "app/view/views/MenuView.h"
#include "app/view/views/GameView.h"

using Bokoblin::SimpleLogger::Logger;

/**
 * Initializes the application and controls its loop
 *
 * @author Arthur, Florian
 * @date 21/02/16 - 12/10/18
 */
int main() //TODO: App class with logic -- main must only uses it + check arguments (for CLI)
{
    //=== Initialize window

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP), APP_TITLE, sf::Style::Close);
    window.setFramerateLimit(APP_FRAMERATE);

    sf::Image appIcon;
    if (appIcon.loadFromFile(ICON_IMAGE)) {
        window.setIcon(appIcon.getSize().x, appIcon.getSize().y, appIcon.getPixelsPtr());
    }

    //=== Initialize app data and text

    AppCore appCore;
    Logger::setLoggerFile("./boko_runner.log");
    PersistenceManager::initContext(appCore);
    PersistenceManager::fetchConfiguration();
    PersistenceManager::fetchStatistics();
    PersistenceManager::fetchLeaderboard();
    LocalizationManager::initContext(appCore);

    mdsf::Config::printError = Logger::printError;
    AppTextManager textManager(&appCore, SCREEN_WIDTH, SCREEN_HEIGHT);

    //=== Initialize app state, and event object

    appCore.setAppState(SPLASH);
    sf::Event event = sf::Event();

    //=== Program loop

    while (window.isOpen()) {
        if (appCore.getAppState() == SPLASH) {
            SplashScreenModel splashModel(&appCore);
            SplashScreenView splashView(&window, &textManager, &splashModel);

            while (appCore.getAppState() == SPLASH && splashView.handleEvents(event)) {
                splashModel.nextStep();
                splashView.synchronize();
                splashView.draw();
            }
        }
        if (appCore.getAppState() == MENU) {
            MenuModel menuModel(&appCore);
            MenuView menuView(&window, &textManager, &menuModel);

            while (appCore.getAppState() == MENU && menuView.handleEvents(event)) {
                menuModel.nextStep();
                menuView.synchronize();
                menuView.draw();
            }
        }
        if (appCore.getAppState() == GAME) {
            GameModel gameModel(SCREEN_WIDTH, SCREEN_HEIGHT, &appCore);
            GameView gameView(&window, &textManager, &gameModel);

            while (appCore.getAppState() == GAME && gameView.handleEvents(event)) {
                gameModel.nextStep();
                gameView.synchronize();
                gameView.draw();
            }
        }
        if (appCore.getAppState() == QUIT) {
            PersistenceManager::updatePersistence();
            window.close();
        }
    }

    PersistenceManager::closeContext();
    LocalizationManager::closeContext();

    return EXIT_SUCCESS;
}
