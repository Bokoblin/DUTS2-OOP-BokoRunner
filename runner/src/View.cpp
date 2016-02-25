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
    m_window->setFramerateLimit(5);


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
    }

    if (!m_ennemiesTexture.loadFromFile(ENNEMIES_IMAGE, sf::IntRect(0,0,50,50)) )     //chargement d'une partie de l'image des balles
        cerr << "ERROR when loading image file: " << ENNEMIES_IMAGE << endl;
    else
    {
        m_ennemiesGraphic = new GraphicElement(m_ennemiesTexture, 400, 450,50,50);
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
// Accesseurs en �criture
//=======================================
void View::setModel(Model *model)
{
    m_model = model;
    m_elementToGraphicElement[m_model->getMovBall()] = m_playerGraphic;//association de la balle et de la balle graphique
}


//=======================================
// Fonction de synchronisation
//=======================================
void View::synchronize()
{
    //=== Association des nouveaux elements de "m_movableElementList" avec des instances de GraphicElement

    for (unsigned int i=1; i<m_model->getMovableElementsList().size(); i++)
    {
        GraphicElement *m_newEnnemy = new GraphicElement(*m_ennemiesGraphic);
        m_elementToGraphicElement[m_model->getMovableElementsList()[i] ] = m_ennemiesGraphic;//m_newEnnemy;
    }

    //=== Vidage de "m_newMovableElementList"

    m_model->getNewMovableElementsList().clear(); //marche pas


    //=== Mise � jour de la position graphique � parir de celle des instances de "MovableElement"

    m_backgroundGraphic->setPosition(sf::Vector2f(0,0));
    m_playerGraphic->setPosition(sf::Vector2f( m_model->getMovBall()->getPosX(), POSITION_Y_BALL));

/* //DEBUG
    cout << "==Contenu tableau APRES EFFACEMENT==" << endl;

    for (unsigned int i=0; i<m_model->getNewMovableElementsList().size(); i++)
    {
        cout << m_model->getNewMovableElementsList()[i] <<  " at adress :  " << &(m_model->getNewMovableElementsList()[i]) << endl;
    }
*/
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
        /* //DEBUG
        cout << "===== DRAW =====" << endl << endl;
        cout << "element at adress " << (it->second) << " has been drawn" <<endl;
        */
    }

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
            case sf::Event::Closed:      // fen�tre ferm�e
                m_window->close();
                break;

            case sf::Event::KeyPressed:  // touche press�e
                if (event.key.code == sf::Keyboard::Escape)
                {
                    m_window->close();
                    result = false;
                }
                if ( (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Q ) && POSITION_X_BALL > 0 )
                {
                    m_model->moveBall(true);
                    cout << POSITION_X_BALL << endl;
                }
                if ( (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D ) && (POSITION_X_BALL + WIDTH_BALL) < m_viewWidth )
                {
                    m_model->moveBall(false);
                    cout << POSITION_X_BALL << endl;
                }
                if (event.key.code == sf::Keyboard::Add)
                {
                    m_model->addNewElement();
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
                    cout << POSITION_X_BALL << endl;
                    cout << "L" << endl;
                }
                else if (sf::Joystick::isButtonPressed(0, 5)  && (POSITION_X_BALL + WIDTH_BALL) < m_viewWidth )
                {
                    m_model->moveBall(false);
                    cout << POSITION_X_BALL << endl;
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

