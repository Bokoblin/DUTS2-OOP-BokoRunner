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
    Default Constructor
*********************************************
    Arthur : 21/02 - 3/03
    Florian: 21/02 - 3/03
*********************************************/
View::View(int w, int h): m_viewWidth(w), m_viewHeight(h)
{
    m_window = new sf::RenderWindow( sf::VideoMode(w, h, 32), "Runner", sf::Style::Close );
    m_window->setFramerateLimit(30);

    if (!m_farBackgroundTexture.loadFromFile(BACKGROUND_IMAGE_2))
        cerr << "ERROR when loading image file: " << BACKGROUND_IMAGE_2 << endl;
    else
    {
        m_farBackground = new SlidingBackground(m_farBackgroundTexture, m_viewWidth, m_viewHeight, 1);
    }

    if (!m_nearBackgroundTexture.loadFromFile(BACKGROUND_IMAGE_1))
        cerr << "ERROR when loading image file: " << BACKGROUND_IMAGE_1 << endl;
    else
    {
        m_nearBackground = new SlidingBackground(m_nearBackgroundTexture, m_viewWidth, m_viewHeight, 4);
    }

    if (!m_playerTexture.loadFromFile(BALL_IMAGE, sf::IntRect(0,0,50,50)) )
        cerr << "ERROR when loading image file: " << BALL_IMAGE << endl;
    else
    {
        m_playerGraphic = new GraphicElement(m_playerTexture, 50, 50,25,25);
        m_playerGraphic->resize(20,20);
    }

    if (!m_ennemiesTexture.loadFromFile(ENNEMIES_IMAGE, sf::IntRect(0,0,50,50)) )
        cerr << "ERROR when loading image file: " << ENNEMIES_IMAGE << endl;
    else
    {
        m_ennemiesGraphic = new GraphicElement(m_ennemiesTexture, 400, 450,20,20);
    }

    //font & text initialization
    m_font = new sf::Font();
    m_font->loadFromFile(FONT);
    m_textPositionBall = new sf::Text;
    m_textPositionBall->setFont(*m_font);
    m_textPositionBall->setPosition(10,10);
    m_textPositionBall->setCharacterSize(15);
    m_textPositionBall->setColor(sf::Color::Black);
}


/********************************************
    Destructor
*********************************************
    Arthur : 21/02 - 2/03
    Florian: 21/02 - 2/03
*********************************************/
View::~View()
{
    if(m_window!= NULL)
        delete m_window;
    if(m_font!= NULL)
        delete m_font;
}


/********************************************
   Setters
*********************************************
    Arthur : 21/02 - 25/02
    Florian: 21/02 - 21/02
*********************************************/
void View::setModel(Model *model)
{
    m_model = model;
    m_elementToGraphicElement[m_model->getBallElement()] = m_playerGraphic; //temp location
}


/********************************************
    Synchronization function
*********************************************
    Arthur : 21/02 - 3/03
    Florian: 21/02 - 3/03
*********************************************/
void View::synchronize()
{
    //=== Pairing of new movable elements and corresponding graphic elements

    for (unsigned int i=0; i<( m_model->getNewMovableElementsList().size() ); i++)
    {
        GraphicElement *m_newEnnemy = new GraphicElement(*m_ennemiesGraphic);
        m_newEnnemy->resize(20,20);

        if (m_elementToGraphicElement.find(m_model->getNewMovableElementsList()[i] ) == m_elementToGraphicElement.end() )
            m_elementToGraphicElement[m_model->getNewMovableElementsList()[i] ] = m_newEnnemy;
    }

    //=== New movable elements vector emptying

    m_model->clearNewMovableElementVector(); //marche pas


    //=== Update positions


    m_playerGraphic->setPosition(sf::Vector2f( POS_X_BALL, POS_Y_BALL));

    //=== Text update

    m_textPositionBall->setString( m_model->getBallElement()->to_string() );

}


/********************************************
    Drawing function
*********************************************
    Arthur : 21/02 - 3/03
    Florian: 21/02 - 3/03
*********************************************/
void View::draw()
{
    m_window->clear();

    //=== Graphical Elements drawing

    m_farBackground->syncAndDraw(*m_window);
    m_nearBackground->syncAndDraw(*m_window);

    for(auto it = m_elementToGraphicElement.begin() ; it != m_elementToGraphicElement.end() ; ++it)
    {
        m_window->draw(*(it->second));
    }

    //=== Text drawing

    m_window->draw(*m_textPositionBall);

    m_window->display();
}


/********************************************
    Events treating
*********************************************
    Arthur : 21/02 - 2/03
    Florian: 21/02 - 2/03
*********************************************/
bool View::treatEvents()
{
    bool result = false;
    if(m_window->isOpen())
    {
        result = true;

        sf::Event event;
        while (m_window->pollEvent(event))
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window->close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                {
                    m_window->close();
                    result = false;
                }
                if ( (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Q ) && POS_X_BALL > 0 )
                {
                    m_model->moveBall(true);
                }
                if ( (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D ) && (POS_X_BALL + WIDTH_BALL) < m_viewWidth )
                {
                    m_model->moveBall(false);
                }
                if (event.key.code == sf::Keyboard::Add)
                {
                    m_model->addNewMovableElement();
                }
                break;
            default:
                break;
            }
    }
    return result;
}
