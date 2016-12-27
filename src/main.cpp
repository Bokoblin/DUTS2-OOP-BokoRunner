/* Copyright 2016 Jolivet Arthur & Laronze Florian

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


/********************************************
    Constant Variables
********************************************/
const int INTRO_WIDTH = 400;
const int INTRO_HEIGHT = 200;


/**
 * Main function
 * @author Arthur, Florian
 * @date 21/02 - 26/12
 */
int main()
{
    sf::RenderWindow window( sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP), APP_TITLE, sf::Style::None );
    window.setFramerateLimit(FRAMERATE);

    DataBase dataBase;
    TextHandler textHandler(&dataBase, SCREEN_WIDTH, SCREEN_HEIGHT);

    while(window.isOpen() )
    {
        if  ( dataBase.getAppState() == INTRO )
        {
            IntroModel introModel(&dataBase);
            IntroView introView(INTRO_WIDTH, INTRO_HEIGHT, &window, &textHandler, &introModel);

            while( dataBase.getAppState() == INTRO && introView.treatEvents() )
            {
                introView.synchronize();
                introView.draw();
            }
        }

        if  ( dataBase.getAppState() == MENU )
        {
            MenuModel menuModel(&dataBase);
            MenuView menuView(SCREEN_WIDTH, SCREEN_HEIGHT, &window, &textHandler, &menuModel);

            while( dataBase.getAppState() == MENU && menuView.treatEvents()  )
            {
                menuModel.nextStep();
                menuView.synchronize();
                menuView.draw();
            }
        }

        if  ( dataBase.getAppState() == GAME )
        {
            GameModel gameModel(SCREEN_WIDTH, SCREEN_HEIGHT, &dataBase);
            GameView gameView(SCREEN_WIDTH, SCREEN_HEIGHT, &window, &textHandler, &gameModel);

            while( dataBase.getAppState() == GAME && gameView.treatEvents() )
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
