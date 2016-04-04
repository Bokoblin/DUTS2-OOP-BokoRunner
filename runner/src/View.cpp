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
    Arthur : 21/02 - 6/03
    Florian: 21/02 - 3/03
*********************************************/
View::View(int w, int h): m_viewWidth(w), m_viewHeight(h)
{
    m_window = new sf::RenderWindow( sf::VideoMode(w, h, 32), "Runner", sf::Style::Close );
    m_window->setFramerateLimit(FRAMERATE);

    //=== Images Loading

    loadImages();

    //=== font & text initialization

    m_font = new sf::Font();
    m_font->loadFromFile(FONT);

    loadText();
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
    if(m_farBackground!= NULL)
        delete m_farBackground;
    if(m_nearBackground!= NULL)
        delete m_nearBackground;
    if(m_playerGraphic!= NULL)
        delete m_playerGraphic;
    if(m_enemiesGraphic!= NULL)
        delete m_enemiesGraphic;
}


/********************************************
   Setters
*********************************************
    Arthur : 21/02 - 5/03
    Florian: 21/02 - 21/02
*********************************************/
void View::setModel(Model *model)
{
    m_model = model;
}


/********************************************
    Image Loading
*********************************************
    Arthur : 5/03 - 13/03
*********************************************/
void View::loadImages()
{
    if (!m_farBackgroundTexture.loadFromFile(BACKGROUND_IMAGE_2))
        cerr << "ERROR when loading image file: " << BACKGROUND_IMAGE_2 << endl;
    else
    {
        m_farBackgroundTexture.setSmooth(true);
        m_farBackground = new SlidingBackground(m_farBackgroundTexture, 1200, m_viewHeight, 1);
    }

    if (!m_nearBackgroundTexture.loadFromFile(BACKGROUND_IMAGE_1))
        cerr << "ERROR when loading image file: " << BACKGROUND_IMAGE_1 << endl;
    else
    {
        m_nearBackgroundTexture.setSmooth(true);
        m_nearBackground = new SlidingBackground(m_nearBackgroundTexture, 1200, m_viewHeight, 4);
    }

    if (!m_playerTexture.loadFromFile(BALL_IMAGE) )
        cerr << "ERROR when loading image file: " << BALL_IMAGE << endl;
    else
    {
        m_playerTexture.setSmooth(true);
        std::vector<sf::IntRect> clip_rects;
        for (int i=0; i<8; i++)
        {
            clip_rects.push_back(sf::IntRect(50*i,0,50,50));
        }
        m_playerGraphic = new AnimatedGraphicElement(clip_rects, m_playerTexture, PLAYER_DEFAULT_POS_X, GAME_FLOOR,50,50);
    }

    if (!m_enemiesTexture.loadFromFile(ENEMIES_IMAGE))
        cerr << "ERROR when loading image file: " << ENEMIES_IMAGE << endl;
    else
    {
        m_enemiesTexture.setSmooth(true);
        std::vector<sf::IntRect> clip_rects;
        for (int i=0; i<2; i++)
        {
            clip_rects.push_back(sf::IntRect(50*i,0,50,50));
        }
        m_enemiesGraphic = new AnimatedGraphicElement(clip_rects, m_enemiesTexture, m_viewWidth, GAME_FLOOR,50,50);
    }
}


/********************************************
    Text Loading
*********************************************
    Arthur : 6/03 - 12/03
*********************************************/
void View::loadText()
{
    m_textPositionBall.setFont(*m_font);
    m_textPositionBall.setPosition(10,10);
    m_textPositionBall.setCharacterSize(15);
    m_textPositionBall.setColor(sf::Color::Black);

    m_textTotalDistance.setFont(*m_font);
    m_textTotalDistance.setPosition(250,10);
    m_textTotalDistance.setCharacterSize(15);
    m_textTotalDistance.setColor(sf::Color::Black);

    m_textchosenInterDistance.setFont(*m_font);
    m_textchosenInterDistance.setPosition(450,10);
    m_textchosenInterDistance.setCharacterSize(15);
    m_textchosenInterDistance.setColor(sf::Color::Black);

    m_textcurrentInterDistance.setFont(*m_font);
    m_textcurrentInterDistance.setPosition(650,10);
    m_textcurrentInterDistance.setCharacterSize(15);
    m_textcurrentInterDistance.setColor(sf::Color::Black);
}


/********************************************
    Update gElements
*********************************************
    Arthur : 6/03 - 13/03
*********************************************/
void View::updateElements()
{
    std::map<MovableElement *, GraphicElement *>::iterator it;
    for(it = m_MovableToGraphicElement.begin() ; it != m_MovableToGraphicElement.end() ; ++it)
    {
        m_model->moveMovableElement((it->first));

        int position_x = (it->first)->getPosX();
        int position_y = (it->first)->getPosY();
        int move_x = (it->first)->getMoveX();
        int move_y = (it->first)->getMoveY();

        it->second->setPosition(sf::Vector2f( position_x+move_x, position_y+move_y ));
        it->second->resize(30,30);
    }
}


/********************************************
    Delete gElement and call mElement delete
*********************************************
    Arthur : 12/03
*********************************************/
void View::deleteElements()
{
    std::map<MovableElement *, GraphicElement *>::iterator it2 = m_MovableToGraphicElement.begin();
    bool trouve = false;
    while (!trouve && it2!=m_MovableToGraphicElement.end() )
    {
        if (it2->first->getType() == 1 && ( it2->second->getPosition().x + it2->second->getLocalBounds().width ) < 0 )
        {
            m_MovableToGraphicElement.erase(it2);
            m_model->deleteMovableElement(const_cast<MovableElement*>(it2->first));
            trouve = true;
        }
        else
            ++it2;
    }
}


/********************************************
    Synchronization function
*********************************************
    Arthur : 21/02 - 12/03
    Florian: 21/02 - 3/03
*********************************************/
void View::synchronize()
{
    //=== Pairing of new mElements with gElements

    for (unsigned int i=0; i<( m_model->getNewMEList().size() ); i++)
    {
        if (m_MovableToGraphicElement.find(m_model->getNewMEList()[i] ) == m_MovableToGraphicElement.end() )
        {
            if (  (m_model->getNewMEList()[i])->getType() == 0  )
                m_MovableToGraphicElement[m_model->getNewMEList()[i] ] = m_playerGraphic;
            if (  (m_model->getNewMEList()[i])->getType() == 1  )
            {
                AnimatedGraphicElement *m_newEnemy = new AnimatedGraphicElement(*m_enemiesGraphic);
                m_MovableToGraphicElement[m_model->getNewMEList()[i] ] = m_newEnemy;
            }
        }
    }
    m_model->clearNewMovableElementList();

    //=== Elements update

    m_nearBackground->setSpeed(m_model->getGameSpeed() );

    updateElements();

    //=== Elements deleting

    deleteElements(); //gElements & mElements deleting if not used anymore

    //=== Text update

    m_textPositionBall.setString( PLAYER->to_string() );
    m_textTotalDistance.setString( "total distance : " + to_string(m_model->getDistance() ) );
    m_textchosenInterDistance.setString( "chosen inter : " + to_string(m_model->m_chosenInterdistance ) );
    m_textcurrentInterDistance.setString( " current inter : " + to_string(m_model->m_currentInterdistance) );

}


/********************************************
    View Drawing
*********************************************
    Arthur : 21/02 - 13/03
    Florian: 21/02 - 3/03
*********************************************/
void View::draw()
{
    /* // DEBUG ONLY
        if (system("CLS")) system("clear");
        for (int i=0; i < m_model->getMEList().size(); i++ )
                cout << m_model->getMEList()[i] << endl;
    */ //adresses statut

    m_window->clear();

    //=== Background drawing

    m_farBackground->syncAndDraw(*m_window);
    m_nearBackground->syncAndDraw(*m_window);

    //=== Graphical Elements drawing

    for(auto it = m_MovableToGraphicElement.begin() ; it != m_MovableToGraphicElement.end() ; ++it)
    {
        it->second->draw(m_window);
    }

    //=== Text drawing

    m_window->draw(m_textPositionBall);
    m_window->draw(m_textTotalDistance);
    m_window->draw(m_textchosenInterDistance);
    m_window->draw(m_textcurrentInterDistance);

    m_window->display();
}


/********************************************
    Events treating
*********************************************
    Arthur : 21/02 - 13/03
    Florian: 21/02 - 2/03
*********************************************/
bool View::treatEvents()
{
    bool result = false;
    if(m_window->isOpen())
    {
        result = true;
        bool inair = m_model->getPlayer()->getPosY()<GAME_FLOOR;
        const_cast<MovableElement*>(m_model->getPlayer())->setFlyingState(inair);


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
                if ( (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Q ) && PLAYER->getPosX()  > 0 )
                {
                   // m_model->moveBallAccordingEvent(true);

                   const_cast<MovableElement*>(m_model->getPlayer())->setDecelerationState(false);
                    const_cast<MovableElement*>(m_model->getPlayer())->MoveLeft();
                      cout
                    << PLAYER->getVector().first
                    << "      " << PLAYER->getVector().second
                    << endl;


                }
                if ( (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D ) && (PLAYER->getPosX() + PLAYER->getWidth()) < m_viewWidth )
                {
                   // m_model->moveBallAccordingEvent(false);

                   const_cast<MovableElement*>(m_model->getPlayer())->setDecelerationState(false);
                   const_cast<MovableElement*>(PLAYER)->MoveRight();
                    cout
                    << PLAYER->getVector().first
                    << "      " << PLAYER->getVector().second
                    <<  "   Si la balle n'est pas en l'air = 0 " << inair << endl;

                }
                if ( (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Space) && !inair )
                {
                            const_cast<MovableElement*>(m_model->getPlayer())->setJumpState(true);

                            cout << inair <<endl;
                }

                break;
            case sf::Event::KeyReleased:
                  if ( (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D ))
                      {

                            const_cast<MovableElement*>(m_model->getPlayer())->setDecelerationState(true);

                      }

                      if ( (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Q ))
                      {

                          const_cast<MovableElement*>(m_model->getPlayer())->setDecelerationState(true);

                      }
                      if ( (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Space ))
                      {
                        //
                      }

                      break;


            default:
                break;

            }
/*if( const_cast<MovableElement*>(m_model->getPlayer())->getFlyingState() == true)
        {
            const_cast<MovableElement*>(m_model->getPlayer())->setVectorY(
            ( const_cast<MovableElement*>(m_model->getPlayer())->getVectorY())+(GRAVITATION/FRAMERATE));

            const_cast<MovableElement*>(m_model->getPlayer())->setPositionY(
                                                        const_cast<MovableElement*>(m_model->getPlayer())->getPosY() + (const_cast<MovableElement*>(m_model->getPlayer())->getVectorY()/FRAMERATE));
        }
        else{
            const_cast<MovableElement*>(m_model->getPlayer())->setPositionY(GAME_FLOOR);
        }
*/
    }
    return result;
}








