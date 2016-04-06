/* Copyright (C) 2016 Jolivet Arthur & Laronze Florian

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

#include "../header/View.h"

using namespace std;

/********************************************
    Parameterized Constructor
*********************************************
    Arthur : 21/02 - 27/03
    Florian: 21/02 - 3/03
*********************************************/
View::View(unsigned int w, unsigned int h, sf::RenderWindow *window):
    m_width(w), m_height(h), m_window{window}
{
    m_text = new Text();
}


/********************************************
    Destructor
*********************************************
    Arthur : 21/02 - 27/03
    Florian: 21/02 - 2/03
*********************************************/
View::~View()
{}


/********************************************
   Getters
*********************************************
    Arthur : 27/03
*********************************************/
sf::RenderWindow* View::getWindow() { return m_window; }


/********************************************
   Setters
*********************************************
    Arthur : 21/02
    Florian: 21/02
*********************************************/
void View::setModel(Model *model) { m_model = model; }
