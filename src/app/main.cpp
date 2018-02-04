/* Copyright 2016-2018 Jolivet Arthur & Laronze Florian

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

#include "app/view/SplashScreenView.h"
#include "app/view/MenuView.h"
#include "app/view/GameView.h"

/**
 * Initializes the application and controls its loop
 *
 * @author Arthur, Florian
 * @date 21/02/16 - 04/02/18
 */
int main()
{
    //=== Initialize window

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP), APP_TITLE, sf::Style::Close);
    window.setFramerateLimit(FRAMERATE);

    sf::Image appIcon;
    if (appIcon.loadFromFile(ICON_IMAGE))
        window.setIcon(appIcon.getSize().x, appIcon.getSize().y, appIcon.getPixelsPtr());

    //=== Initialize app data and text

    DataBase dataBase;
    PersistenceManager::initPersistenceManager(&dataBase);
    PersistenceManager::checkPersistence();
    PersistenceManager::fetchConfiguration();
    PersistenceManager::fetchLeaderboard();
    AppTextManager textManager(&dataBase, SCREEN_WIDTH, SCREEN_HEIGHT);

    //=== Initialize app state, and event object

    dataBase.setAppState(SPLASH);
    sf::Event event = sf::Event();

    //=== Program loop

    while(window.isOpen())
    {
        if (dataBase.getAppState() == SPLASH)
        {
            SplashScreenModel splashModel(&dataBase);
            SplashScreenView splashView(&window, &textManager, &splashModel);

            while(dataBase.getAppState() == SPLASH && splashView.handleEvents(event))
            {
                splashModel.nextStep();
                splashView.synchronize();
                splashView.draw();
            }
        }
        if (dataBase.getAppState() == MENU)
        {
            MenuModel menuModel(&dataBase);
            MenuView menuView(&window, &textManager, &menuModel);

            while(dataBase.getAppState() == MENU && menuView.handleEvents(event))
            {
                menuModel.nextStep();
                menuView.synchronize();
                menuView.draw();
            }
        }
        if (dataBase.getAppState() == GAME)
        {
            GameModel gameModel(SCREEN_WIDTH, SCREEN_HEIGHT, &dataBase);
            GameView gameView(&window, &textManager, &gameModel);

            while(dataBase.getAppState() == GAME && gameView.handleEvents(event))
            {
                gameModel.nextStep();
                gameView.synchronize();
                gameView.draw();
            }
        }
        if (dataBase.getAppState() == QUIT)
        {
            PersistenceManager::updatePersistence();
            window.close();
        }
    }

    PersistenceManager::closePersistenceManager();

    return 0;
}
