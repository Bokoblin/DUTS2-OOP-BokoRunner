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

#include "view/Intro.h"
#include "view/MenuView.h"
#include "view/GameView.h"

/**
 * The main function initializes the application
 * @author Arthur, Florian
 * @date 21/02/16 - 25/01/17
 */
int main()
{
    sf::RenderWindow window( sf::VideoMode(SCREEN_WIDTH,
            SCREEN_HEIGHT, SCREEN_BPP), APP_TITLE, sf::Style::None );
    window.setFramerateLimit(FRAMERATE);

    DataBase data;
    Model model(SCREEN_WIDTH, SCREEN_HEIGHT);
    model.setDataBase(&data);
    TextHandler textHandler(&data, SCREEN_WIDTH, SCREEN_HEIGHT);

    while(window.isOpen() )
    {
        if  ( model.getAppState() == INTRO )
        {
            Intro intro(INTRO_WIDTH, INTRO_HEIGHT, &window, &textHandler);
            intro.setModel(&model);
            while( model.getAppState() == INTRO && intro.treatEvents() )
            {
                intro.synchronize();
                intro.draw();
            }
        }

        if  ( model.getAppState() == MENU )
        {
            MenuModel mModel(model);
            mModel.setDataBase(&data);
            MenuView mView(SCREEN_WIDTH, SCREEN_HEIGHT, &window, &textHandler);
            mView.setModel(&model);
            mView.setMenuModel(&mModel);
            while( model.getAppState() == MENU && mView.treatEvents()  )
            {
                mModel.nextStep();
                mView.synchronize();
                mView.draw();
            }
        }

        if  ( model.getAppState() == GAME )
        {
            GameModel gModel(model);
            gModel.setDataBase(&data);
            GameView gView(SCREEN_WIDTH, SCREEN_HEIGHT, &window, &textHandler);
            gView.setModel(&model);
            gView.setGameModel(&gModel);
            while( model.getAppState() == GAME && gView.treatEvents() )
            {
                gModel.nextStep();
                gView.synchronize();
                gView.draw();
            }
            if ( model.getAppState() == RESET_GAME )
            {
                model.setAppState(GAME);
            }
        }
    }

    data.pushConfigurationToFile();

    return EXIT_SUCCESS;
}
