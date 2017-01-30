/* Copyright 2016-2017 Jolivet Arthur & Laronze Florian

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

#include "view/IntroView.h"
#include "view/MenuView.h"
#include "view/GameView.h"

/**
 * The main function initializes the application
 * @author Arthur, Florian
 * @date 21/02/16 - 30/01/17
 */
int main()
{
    sf::RenderWindow window( sf::VideoMode(SCREEN_WIDTH,
            SCREEN_HEIGHT, SCREEN_BPP), APP_TITLE, sf::Style::None );
    window.setFramerateLimit(FRAMERATE);

    DataBase dataBase;
    TextHandler textHandler(&dataBase, SCREEN_WIDTH, SCREEN_HEIGHT);
    sf::Event event = sf::Event();

    while(window.isOpen() )
    {
        if  ( dataBase.getAppState() == INTRO )
        {
            IntroModel introModel(&dataBase);
            IntroView introView(INTRO_WIDTH, INTRO_HEIGHT, &window, &textHandler, &introModel);

            while( dataBase.getAppState() == INTRO && introView.treatEvents(event) )
            {
                introView.synchronize();
                introView.draw();
            }
        }

        if  ( dataBase.getAppState() == MENU )
        {
            MenuModel menuModel(&dataBase);
            MenuView menuView(SCREEN_WIDTH, SCREEN_HEIGHT, &window, &textHandler, &menuModel);

            while( dataBase.getAppState() == MENU && menuView.treatEvents(event)  )
            {
                menuModel.nextStep();
                menuView.synchronize();
                menuView.draw();
            }
        }

        if  ( dataBase.getAppState() == GAME )
        {
            GameModel gameModel(SCREEN_WIDTH, SCREEN_HEIGHT, &dataBase);
            GameView gameView(&window, &textHandler, &gameModel);

            while( dataBase.getAppState() == GAME && gameView.treatEvents(event) )
            {
                gameModel.nextStep();
                gameView.synchronize();
                gameView.draw();
            }
            if ( dataBase.getAppState() == RESET_GAME )
            {
                dataBase.setAppState(GAME);
            }
        }
    }

    dataBase.pushConfigurationToFile();

    return EXIT_SUCCESS;
}
