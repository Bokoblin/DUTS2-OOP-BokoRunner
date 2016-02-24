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

//=======================================
// Constructeur
//=======================================
View::View(int w, int h): m_viewWidth(w), m_viewHeight(h)
{
    m_window = new sf::RenderWindow( sf::VideoMode(w, h, 32), "Runner", sf::Style::Close );

    if (!m_backgroundTexture.loadFromFile(BACKGROUND_IMAGE))
        cerr << "ERROR when loading image file: " << BACKGROUND_IMAGE << endl;
    else
    {
        m_backgroundGraphic = new GraphicElement(m_backgroundTexture, 0, 0, m_viewWidth, m_viewHeight);
    }

    if (!m_playerTexture.loadFromFile(BALL_IMAGE, sf::IntRect(0,0,50,50)) )     //chargement d'une partie de l'image des balles
        cerr << "ERROR when loading image file: " << BALL_IMAGE << endl;
    else
    {
        m_playerGraphic = new GraphicElement(m_playerTexture, 50, 50,25,25);
        m_playerGraphic->resize(20,20);

        m_elementToGraphicElement[m_model->getBallAdr()] = m_playerGraphic; //association de la balle et de la balle graphique
    }


    m_font = new sf::Font();
    m_font->loadFromFile(FONT);
    m_textPositionBall = new sf::Text;
    m_textPositionBall->setFont(*m_font);
    m_textPositionBall->setPosition(10,10);
    m_textPositionBall->setCharacterSize(15);
    m_textPositionBall->setColor(sf::Color::Black);
}


//=======================================
// Destructeur
//=======================================
View::~View()
{
    if(m_window!= NULL)
        delete m_window;
//    if(m_font!= NULL)
    //     delete m_font;
}


//=======================================
// Accesseurs en écriture
//=======================================
void View::setModel(Model *model)
{
    m_model = model;
}


//=======================================
// Fonction de synchronisation
//=======================================
void View::synchronize()
{
    //!!!!!! A CHANGER : seul les movable sont autorisés (atelier 3 II. 1.2 bis )

    //Mise à jour des instances de MovableElement
    m_backgroundGraphic->setPosition(sf::Vector2f(0,0));
    m_playerGraphic->setPosition(sf::Vector2f(POSITION_X_BALL, POSITION_Y_BALL));

    //atelier 3 2.3 :
    //modifier la méthode synchronize afin d'instancier un nouvel objet graphique pour
    // chaque nouvel élément du modèle et mettre à jour le tableau associatif.


    //Mise à jour du texte

    m_textPositionBall->setString(m_model->getBall().to_string());
    //m_textePosBallY.setString(std::to_string(POSITION_Y_BALL));
}


//=======================================
// Fonction de dessin
//=======================================
void View::draw()
{
    m_window->clear();

    //Dessin des instances de GraphicElement
    m_window->draw(*m_backgroundGraphic);

    for(it = m_elementToGraphicElement.begin() ; it != m_elementToGraphicElement.end() ; ++it)
    {
        m_window->draw(*(it->second));
    }

    m_window->draw(*m_textPositionBall);

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
                if ( (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Q ) && POSITION_X_BALL > 0 )
                {
                    m_model->moveBall(true);
                }
                if ( (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D ) && (POSITION_X_BALL + WIDTH_BALL) < m_viewWidth )
                {
                    m_model->moveBall(false);
                }
                if (event.key.code == sf::Keyboard::Add)
                {
                    m_model->addElement();
                }
                break;

            //{  Joystick
            case sf::Event::JoystickConnected :
                cout << "connected" << endl;
                break;
            case sf::Event::JoystickDisconnected :
                cout << "Disconnected" << endl;
                break;
            case sf::Event::JoystickButtonPressed :
                if (sf::Joystick::isButtonPressed(0, 0) )
                    cout << "X" << endl;
                else if (sf::Joystick::isButtonPressed(0, 1))
                    cout << "A" << endl;
                else if (sf::Joystick::isButtonPressed(0, 2))
                    cout << "B" << endl;
                else if (sf::Joystick::isButtonPressed(0, 3))
                    cout << "Y" << endl;
                else if (sf::Joystick::isButtonPressed(0, 4) && POSITION_X_BALL > 0 )
                {
                    m_model->moveBall(true);
                    cout << "L" << endl;
                }
                else if (sf::Joystick::isButtonPressed(0, 5)  && (POSITION_X_BALL + WIDTH_BALL) < m_viewWidth )
                {
                    m_model->moveBall(false);
                    cout << "R" << endl;
                }
                else if (sf::Joystick::isButtonPressed(0, 8))
                    cout << "Select" << endl;
                else if (sf::Joystick::isButtonPressed(0, 9))
                {
                    cout << "Start" << endl;
                    m_window->close();
                    result = false;
                }
                break;
            //}
            default:
                break;
            }
        }
    }
    return result;
}

