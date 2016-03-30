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

#include "../header/Intro.h"

using namespace std;

/********************************************
    Parameterized Constructor
*********************************************
    Arthur : 27/03
*********************************************/
Intro::Intro(int w, int h, sf::RenderWindow *window): View(w, h, window)
{
    m_window->create( sf::VideoMode(w, h, 32), "Boko Runner", sf::Style::None );
    m_window->setFramerateLimit(30);
    m_window->setPosition(sf::Vector2i( (sf::VideoMode::getDesktopMode().width - m_width)/2, (sf::VideoMode::getDesktopMode().height - m_height)/2 ));

    loadImages();
}


/********************************************
    Destructor
*********************************************
    Arthur : 27/03
*********************************************/
Intro::~Intro()
{
    if(m_introGraphic!= NULL)
        delete m_introGraphic;
}


/********************************************
    Image Loading
*********************************************
    Arthur : 27/03
*********************************************/
void Intro::loadImages()
{
    if (!m_introTexture.loadFromFile(INTRO_IMAGE))
        cerr << "ERROR when loading image file: " << INTRO_IMAGE << endl;
    else
    {
        m_introTexture.setSmooth(true);
        m_introGraphic = new GraphicElement(m_introTexture, 0,0, 400, 200);
    }
}


/********************************************
    Synchronization function
*********************************************
    Arthur : 27/03
*********************************************/
void Intro::synchronize()
{ }


/********************************************
    View Drawing
*********************************************
    Arthur : 27/03
*********************************************/
void Intro::draw()
{
    m_window->clear();

    m_window->draw(*m_introGraphic);

    m_window->display();
}


/********************************************
    Events treating
*********************************************
    Arthur : 27/03
*********************************************/
bool Intro::treatEvents()
{
    bool result = false;

    if(m_window->isOpen())
    {
        result = true;

        sf::Event event;
        while (m_window->pollEvent(event))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_model->getIntroState() == true)
            {
                m_model->setIntroState(false);
                m_model->setMenuState(true);
            }
        }
    }
    return result;
}
