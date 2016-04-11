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

#include "header/Menu.h"
#include "header/Intro.h"
#include "header/GameView.h"


const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;
const std::chrono::system_clock::time_point programBeginningTime = std::chrono::system_clock::now();

using namespace std;

/********************************************
    Main function
*********************************************
    Arthur : 21/02 - 03/03
    Florian: 21/02 - 21/02
*********************************************/
int main()
{
    srand(time(NULL));
    sf::RenderWindow *window = new sf::RenderWindow( sf::VideoMode(SCREEN_WIDTH,
                                                                    SCREEN_HEIGHT, 32), "Boko Runner", sf::Style::None );
    window->setFramerateLimit(30);

    Model model(SCREEN_WIDTH, SCREEN_HEIGHT, programBeginningTime);

    while(window->isOpen() )
    {
        if  (model.getIntroState() == true)
        {
            Intro intro(400, 200, window);
            intro.setModel(&model);
            while( model.getIntroState() && intro.treatEvents() )
            {
                intro.synchronize();
                intro.draw();
            }
        }

        if  (model.getMenuState() == true)
        {
            Menu menu(SCREEN_WIDTH, SCREEN_HEIGHT, window);
            menu.setModel(&model);
            while( model.getMenuState() && menu.treatEvents()  )
            {
                menu.synchronize();
                menu.draw();
            }
        }

        if  (model.getGameState() == true)
        {
            GameModel gModel(SCREEN_WIDTH, SCREEN_HEIGHT, programBeginningTime);
            GameView gView(SCREEN_WIDTH, SCREEN_HEIGHT, window);
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

    delete window;

    return EXIT_SUCCESS;
}
