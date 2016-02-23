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

#include <sstream>
#include <iostream>

using namespace std;


//=======================================
// Constructeur
//=======================================
View::View(int w, int h): m_viewWidth(w), m_viewHeight(h)
{
    m_window = new sf::RenderWindow( sf::VideoMode(w, h, 32), "Runner", sf::Style::Close );

    if (!m_background.loadFromFile(BACKGROUND_IMAGE))
        cerr << "ERROR when loading image file: " << BACKGROUND_IMAGE << endl;
    else
    {
        m_backgroundSprite.setTexture(m_background);
        //m_backgroundSprite.setPosition(sf::Vector2f(0.f,0.f));
        GraphicElement graphicBackground();
    }

    if (!m_ball.loadFromFile(BALL_IMAGE))
        cerr << "ERROR when loading image file: " << BALL_IMAGE << endl;
    else
    {
        m_ballSprite.setTexture(m_ball);
        //m_ballSprite.setPosition(sf::Vector2f(50.f,450.f));
        GraphicElement graphicBall();
    }
}


//=======================================
// Destructeur
//=======================================
View::~View()
{
    if(m_window!= NULL)
        delete m_window;
}



//=======================================
// Accesseurs en écriture
//=======================================
void View::setModel(Model *model) { m_model = model; }



//=======================================
// Fonction de synchronisation
//=======================================
void View::synchronize()
{
    m_ballSprite.setPosition(sf::Vector2f(POSITION_X_BALL, POSITION_Y_BALL));
//    graphicBall.setPosition(sf::Vector2f(POSITION_X_BALL, POSITION_Y_BALL));
}

//=======================================
// Fonction de dessin
//=======================================
void View::draw()
{
    m_window->clear();

    m_window->draw(m_backgroundSprite);
    m_window->draw(m_ballSprite);

    m_window->display();
}



//=======================================
// Traitement des evenements
//=======================================
bool View::treatEvents()
{
    bool result = false;
    if(m_window->isOpen())
    {
        result = true;

        sf::Event event;
        while (m_window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:             // fenêtre fermée
                m_window->close();
                break;

            case sf::Event::KeyPressed:     // touche pressée
                if (event.key.code == sf::Keyboard::Escape)
                {
                    m_window->close();
                    result = false;
                }
                if ( (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Q) && POSITION_X_BALL > 0 )
                {
                    m_model->moveBall(true);
                    cout << POSITION_X_BALL << endl;
                }
                if ( (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) && (POSITION_X_BALL + WIDTH_BALL) < m_viewWidth )
                {
                    m_model->moveBall(false);
                    cout << POSITION_X_BALL << endl;
                }
                break;
            default:
                break;
            }
        }
    }
    return result;
}

