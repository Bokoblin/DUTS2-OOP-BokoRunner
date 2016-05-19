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

#include "header/Intro.h"
#include "header/MenuView.h"
#include "header/GameView.h"


/********************************************
    Constant Variables
********************************************/
const int INTRO_WIDTH = 400;
const int INTRO_HEIGHT = 200;
const std::chrono::system_clock::time_point programBeginningTime = std::chrono::system_clock::now();

using namespace std;


/********************************************
    Main function
*********************************************
    @author Arthur  @date 21/02 - 06/05
    @author Florian  @date 21/02
*********************************************/
int main()
{
    srand(time(NULL));
    sf::RenderWindow *window = new sf::RenderWindow( sf::VideoMode(SCREEN_WIDTH,
            SCREEN_HEIGHT, SCREEN_BPP), APP_TITLE, sf::Style::None );
    window->setFramerateLimit(FRAMERATE);

    DataBase data;
    Model model(SCREEN_WIDTH, SCREEN_HEIGHT, programBeginningTime);
    model.setDataBase(&data);
    Text *text = new Text(&data);

    while(window->isOpen() )
    {
        if  (model.getIntroState() == true)
        {
            Intro intro(INTRO_WIDTH, INTRO_HEIGHT, window, text);
            intro.setModel(&model);
            while( model.getIntroState() && intro.treatEvents() )
            {
                intro.synchronize();
                intro.draw();
            }
        }

        if  (model.getMenuState() == true)
        {
            MenuModel mModel(model);
            mModel.setDataBase(&data);
            MenuView mView(SCREEN_WIDTH, SCREEN_HEIGHT, window, text);
            mView.setModel(&model);
            mView.setMenuModel(&mModel);
            while( model.getMenuState() && mView.treatEvents()  )
            {
                mModel.nextStep();
                mView.synchronize();
                mView.draw();
            }
        }

        if  (model.getGameState() == true)
        {
            GameModel gModel(model);
            gModel.setDataBase(&data);
            GameView gView(SCREEN_WIDTH, SCREEN_HEIGHT, window, text);
            gView.setModel(&model);
            gView.setGameModel(&gModel);
            while( model.getGameState() && gView.treatEvents() )
            {
                gModel.nextStep();
                gView.synchronize();
                gView.draw();
            }
            if (model.getResetGameState() == true)
            {
                model.setGameState(true);
                model.setResetGameState(false);
            }
        }
    }

    data.pushConfigurationToFile();

    delete text;
    delete window;

    return EXIT_SUCCESS;
}
