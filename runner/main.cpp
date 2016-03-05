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
#include "header/Model.h"

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;

/********************************************
    Main function
*********************************************
    Arthur : 21/02 - 25/02
    Florian: 21/02 - 21/02
*********************************************/
int main()
{
    srand(time(NULL));

    Model model(SCREEN_WIDTH, SCREEN_HEIGHT);
    View view(SCREEN_WIDTH, SCREEN_HEIGHT);
    view.setModel(&model);
    model.addBallMovableElement();
    while(view.treatEvents())
    {
        //model.nextStep();
        view.synchronize();
        view.draw();
    }

    return EXIT_SUCCESS;
}
