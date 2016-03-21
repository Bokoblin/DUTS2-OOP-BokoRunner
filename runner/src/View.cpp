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
    m_window->setFramerateLimit(30);

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
    if(m_bottomBarGraphic!= NULL)
        delete m_bottomBarGraphic;
    if(m_lifeBoxGraphic!= NULL)
        delete m_lifeBoxGraphic;
    if(m_playerGraphic!= NULL)
        delete m_playerGraphic;
    if(m_standardEnemyGraphic!= NULL)
        delete m_standardEnemyGraphic;
    if(m_totemEnemyGraphic!= NULL)
        delete m_totemEnemyGraphic;
    if(m_blockEnemyGraphic!= NULL)
        delete m_blockEnemyGraphic;
    if(m_explosionGraphic!= NULL)
        delete m_explosionGraphic;
    if(m_coinGraphic!= NULL)
        delete m_coinGraphic;
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
    Arthur : 5/03 - 15/03
*********************************************/
void View::loadImages()
{
    if (!m_farBackgroundTexture.loadFromFile(BACKGROUND_IMAGE_2))
        cerr << "ERROR when loading image file: " << BACKGROUND_IMAGE_2 << endl;
    else
    {
        m_farBackgroundTexture.setSmooth(true);
        m_farBackground = new SlidingBackground(m_farBackgroundTexture, 1200, m_viewHeight, 2);
    }

    if (!m_nearBackgroundTexture.loadFromFile(BACKGROUND_IMAGE_1))
        cerr << "ERROR when loading image file: " << BACKGROUND_IMAGE_1 << endl;
    else
    {
        m_nearBackgroundTexture.setSmooth(true);
        m_nearBackground = new SlidingBackground(m_nearBackgroundTexture, 1200, m_viewHeight, 4);
    }

    if (!m_bottomBarTexture.loadFromFile(BOTTOM_BAR))
        cerr << "ERROR when loading image file: " << BOTTOM_BAR << endl;
    else
    {
        m_bottomBarTexture.setSmooth(true);
        m_bottomBarGraphic = new GraphicElement(m_bottomBarTexture, 0, 520, 1200, m_viewHeight);
    }

    if (!m_lifeBoxTexture.loadFromFile(LIFE_BOX))
        cerr << "ERROR when loading image file: " << LIFE_BOX << endl;
    else
    {
        m_lifeBoxTexture.setSmooth(true);
        m_lifeBoxGraphic = new GraphicElement(m_lifeBoxTexture, 105, 535, 200, 100);
    }

    if (!m_playerTexture.loadFromFile(BALL_IMAGE) )
        cerr << "ERROR when loading image file: " << BALL_IMAGE << endl;
    else
    {
        std::vector<sf::IntRect> clip_rects;
        for (int i=0; i<8; i++)
            clip_rects.push_back(sf::IntRect(50*i,0,50,50));

        m_playerTexture.setSmooth(true);
        m_playerGraphic = new AnimatedGraphicElement(clip_rects, m_playerTexture, PLAYER_DEFAULT_POS_X, GAME_FLOOR,50,50);
        m_playerGraphic->setOrigin(0,50);
    }

    if (!m_standardEnemyTexture.loadFromFile(ENEMIES_IMAGE))
        cerr << "ERROR when loading image file: " << ENEMIES_IMAGE << endl;
    else
    {
        std::vector<sf::IntRect> clip_rects;
        for (int i=0; i<2; i++)
            clip_rects.push_back(sf::IntRect(50*i,0,50,50));

        m_standardEnemyTexture.setSmooth(true);
        m_standardEnemyGraphic = new AnimatedGraphicElement(clip_rects, m_standardEnemyTexture, m_viewWidth, GAME_FLOOR,50,50);
        m_standardEnemyGraphic->setOrigin(0,50);
    }

    if (!m_totemEnemyTexture.loadFromFile(ENEMIES_IMAGE))
        cerr << "ERROR when loading image file: " << ENEMIES_IMAGE << endl;
    else
    {
        std::vector<sf::IntRect> clip_rects;
        for (int i=0; i<2; i++)
            clip_rects.push_back(sf::IntRect(50*i,0,50,150));

        m_totemEnemyTexture.setSmooth(true);
        m_totemEnemyGraphic = new AnimatedGraphicElement(clip_rects, m_totemEnemyTexture, m_viewWidth, GAME_FLOOR,50,150);
        m_totemEnemyGraphic->setOrigin(0,150);
    }

    if (!m_blockEnemyTexture.loadFromFile(BLOCK_ENEMIES_IMAGE))
        cerr << "ERROR when loading image file: " << BLOCK_ENEMIES_IMAGE << endl;
    else
    {
        std::vector<sf::IntRect> clip_rects;
        for (int i=0; i<2; i++)
            clip_rects.push_back(sf::IntRect(50*i,0,50,50));

        m_blockEnemyTexture.setSmooth(true);
        m_blockEnemyGraphic = new AnimatedGraphicElement(clip_rects, m_blockEnemyTexture, m_viewWidth, GAME_FLOOR,50,50);
        m_blockEnemyGraphic->setOrigin(0,50);
    }

    if (!m_explosionTexture.loadFromFile(EXPLOSION_IMAGE))
        cerr << "ERROR when loading image file: " << EXPLOSION_IMAGE << endl;
    else
    {
        std::vector<sf::IntRect> clip_rects;
        for (int i=0; i<3; i++)
            clip_rects.push_back(sf::IntRect(200*i,0,200,200));

        m_explosionTexture.setSmooth(true);
        m_explosionGraphic = new AnimatedGraphicElement(clip_rects, m_explosionTexture, m_viewWidth, GAME_FLOOR,50,50);
        m_explosionGraphic->setOrigin(0,50);
    }

    if (!m_coinTexture.loadFromFile(BONUS_IMAGE))
        cerr << "ERROR when loading image file: " << BONUS_IMAGE << endl;
    else
    {
        std::vector<sf::IntRect> clip_rects;
        for (int i=0; i<5; i++)
            clip_rects.push_back(sf::IntRect(50*i,0,50,50));

        m_coinTexture.setSmooth(true);
        m_coinGraphic = new AnimatedGraphicElement(clip_rects, m_coinTexture, 200, GAME_FLOOR,50,50);
        m_coinGraphic->setOrigin(0,50);
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
    m_textPositionBall.setString( "" );

    m_textScore.setFont(*m_font);
    m_textScore.setPosition(720,545);
    m_textScore.setCharacterSize(24);
    m_textScore.setColor(sf::Color::White);
    m_textScore.setString( "" );

    m_textTotalDistance.setFont(*m_font);
    m_textTotalDistance.setPosition(480,545);
    m_textTotalDistance.setCharacterSize(24);
    m_textTotalDistance.setColor(sf::Color::White);
    m_textTotalDistance.setString( "" );

    m_textPlayerLife.setFont(*m_font);
    m_textPlayerLife.setPosition(30,545);
    m_textPlayerLife.setCharacterSize(24);
    m_textPlayerLife.setColor(sf::Color::White);
    m_textPlayerLife.setString( "Life " );
}


/********************************************
    Link mElements with gElements
*********************************************
    Arthur : 18/03
*********************************************/
void View::linkElements()
{
    for (unsigned int i=0; i<( m_model->getNewMElementsArray().size() ); i++)
    {
        if (m_MovableToGraphicElement.find(m_model->getNewMElementsArray()[i] ) == m_MovableToGraphicElement.end() )
        {
            if (  (m_model->getNewMElementsArray()[i])->getType() == 0  )
                m_MovableToGraphicElement[m_model->getNewMElementsArray()[i] ] = m_playerGraphic;
            else if (  (m_model->getNewMElementsArray()[i])->getType() == 1  )
            {
                AnimatedGraphicElement *m_newEnemy;
                if ((m_model->getNewMElementsArray()[i])->getEnemyType() == 0)
                    m_newEnemy = new AnimatedGraphicElement(*m_standardEnemyGraphic);
                else if ((m_model->getNewMElementsArray()[i])->getEnemyType() == 1)
                    m_newEnemy = new AnimatedGraphicElement(*m_totemEnemyGraphic);
                else
                    m_newEnemy = new AnimatedGraphicElement(*m_blockEnemyGraphic);
                m_MovableToGraphicElement[m_model->getNewMElementsArray()[i] ] = m_newEnemy;
            }
            else if (  (m_model->getNewMElementsArray()[i])->getType() == 2  )
            {
                AnimatedGraphicElement *m_newcoin = new AnimatedGraphicElement(*m_coinGraphic);
                m_MovableToGraphicElement[m_model->getNewMElementsArray()[i] ] = m_newcoin;
            }
        }
    }
    m_model->clearNewMovableElementList();
}


/********************************************
    Update gElements
*********************************************
    Arthur : 6/03 - 19/03
*********************************************/
void View::updateElements()
{
    std::map<MovableElement *, GraphicElement *>::iterator it;
    for(it = m_MovableToGraphicElement.begin() ; it != m_MovableToGraphicElement.end() ; ++it)
    {
        //=== Update Position

        m_model->moveMovableElement(it->first);

        int position_x = (it->first)->getPosX();
        int position_y = (it->first)->getPosY();
        int move_x = (it->first)->getMoveX();
        int move_y = (it->first)->getMoveY();

        it->second->setPosition(sf::Vector2f( position_x+move_x, position_y+move_y ));

        //=== Update Graphics

        if (it->first->getType() == 0) //player
        {
            it->second->resize(30,30);
        }
        else if (it->first->getType() == 1) //enemy
        {
            if ( m_playerGraphic->getGlobalBounds().intersects(it->second->getGlobalBounds() ) )
            {
                it->second->setTexture(m_explosionTexture);
                (it->first)->setCollisionState(true);
                if (it->first->getEnemyType() == 0)
                    const_cast<MovableElement*>(PLAYER)->setLife(PLAYER->getLife() -10);
                if (it->first->getEnemyType() == 1)
                    const_cast<MovableElement*>(PLAYER)->setLife(PLAYER->getLife() -15);
                if (it->first->getEnemyType() == 2)
                    const_cast<MovableElement*>(PLAYER)->setLife(PLAYER->getLife() -20);
                cout << "Life = " << PLAYER->getLife() << endl;
            }

            if (it->first->getEnemyType() == 1)
            {
                it->second->resize(30,90);
            }

            else if (it->first->getEnemyType() )
                it->second->resize(50,50);
            else
                it->second->resize(30,30);
        }
        else if (it->first->getType() == 2) //coins
        {
            it->second->resize(25,25);
            if (m_playerGraphic->getGlobalBounds().intersects(it->second->getGlobalBounds() ) )
            {
                (it->first)->setCollisionState(true);
                m_model->setCoinPickedUp();
            }
        }

    }
}


/********************************************
    Delete gElement
*********************************************
    Arthur : 12/03 - 20/03
*********************************************/
void View::deleteElements()
{
    std::map<MovableElement *, GraphicElement *>::iterator it = m_MovableToGraphicElement.begin();
    bool found = false;
    while (!found && it!=m_MovableToGraphicElement.end() )
    {
        if ( (it->first)->getCollisionState() == true )
        {
            delete it->second;
            m_MovableToGraphicElement.erase(it);
            found = true;
        }
        else
            ++it;
    }
}


/********************************************
    Synchronization function
*********************************************
    Arthur : 21/02 - 15/03
    Florian: 21/02 - 3/03
*********************************************/
void View::synchronize()
{
    //=== Link new mElements with gElements

    linkElements();

    //=== Elements deleting if not used anymore

    deleteElements();

    //=== Elements update

    m_nearBackground->setSpeed(m_model->getGameSpeed() );
    updateElements();

    //=== Text update

    //m_textPositionBall.setString( PLAYER->to_string() );
    m_textScore.setString( "Score : " + to_string(m_model->getScore() ) );
    m_textTotalDistance.setString( "Distance : " + to_string(m_model->getDistance() ) + " m" );
}


/********************************************
    View Drawing
*********************************************
    Arthur : 21/02 - 13/03
    Florian: 21/02 - 3/03
*********************************************/
void View::draw()
{
    m_window->clear();

    //=== Background drawing

    m_farBackground->syncAndDraw(*m_window);
    m_nearBackground->syncAndDraw(*m_window);
    m_window->draw(*m_bottomBarGraphic);
    m_window->draw(*m_lifeBoxGraphic);

    //=== Graphical Elements drawing

    for(auto it = m_MovableToGraphicElement.begin() ; it != m_MovableToGraphicElement.end() ; ++it)
    {
        it->second->draw(m_window);
    }

    //=== Text drawing

    //m_window->draw(m_textPositionBall);
    m_window->draw(m_textScore);
    m_window->draw(m_textTotalDistance);
    m_window->draw(m_textPlayerLife);

    m_window->display();
}


/********************************************
    Events treating
*********************************************
    Arthur : 21/02 - 19/03
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
        {
            if  (event.type == sf::Event::Closed)
            {
                m_window->close();
                result = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                m_window->close();
                result = false;
            }
        }
        if ( (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left ) )
            && PLAYER->getPosX()  > 0 )
        {
            m_model->moveBallAccordingEvent(true);
        }
        if ( (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right ) )
            && (PLAYER->getPosX() + PLAYER->getWidth()) < m_viewWidth )
        {
            m_model->moveBallAccordingEvent(false);
        }
    }
    return result;
}
