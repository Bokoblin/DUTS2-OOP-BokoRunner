/*
Copyright (C) 2015 Jolivet Arthur & Laronze Florian

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include "header/View.h"
#include "header/Menu.h"
#include "header/Intro.h"
#include "header/GameView.h"
#include "header/GameModel.h"
#include <iostream>

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;

using namespace std;

/********************************************
    Main function
*********************************************
    Arthur : 21/02 - 26/03
    Florian: 21/02 - 21/02
*********************************************/
int main()
{
    srand(time(NULL));
    sf::RenderWindow *window = new sf::RenderWindow( sf::VideoMode(SCREEN_WIDTH,
                                                                    SCREEN_HEIGHT, 32), "Boko Runner", sf::Style::None );
    window->setFramerateLimit(30);
    Model model(SCREEN_WIDTH, SCREEN_HEIGHT);
    View view(SCREEN_WIDTH, SCREEN_HEIGHT, window);
    view.setModel(&model);

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
            GameModel gModel(SCREEN_WIDTH, SCREEN_HEIGHT);
            GameView gView(SCREEN_WIDTH, SCREEN_HEIGHT, window);
            gView.setGameModel(&gModel);
            while( model.getGameState() && gView.treatEvents() )
            {
                gModel.nextStep();
                gView.synchronize();
                gView.draw();
            }
        }
    }

    return EXIT_SUCCESS;
}
