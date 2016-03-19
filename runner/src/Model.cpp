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

#include "../header/Model.h"

using namespace std;

/********************************************
    Parameterized Constructor
*********************************************
    Arthur : 21/02 - 12/03
    Florian: 21/02 - 2/03
*********************************************/
Model::Model(int width, int height)
    :  m_modelWidth(width), m_modelHeight(height)
{
    m_totalDistance = 0;
    m_gameSpeed = 4;
    m_currentEnemyInterdistance = 0;
    m_currentCoinInterdistance = 0;
    m_chosenEnemyInterdistance = 10 +rand()%10;
    m_chosenCoinInterdistance = 5;
    m_lastTime = clock();
    m_nbCoinsPickedUp = 0;
}


/********************************************
    Destructor
*********************************************
    Arthur : 21/02 - 13/03
    Florian: 21/02 - 2/03
*********************************************/
Model::~Model()
{
    /*   //SEGFAULT ZONE
       if(m_player != NULL) delete m_player;

       for (unsigned int i=0; i < m_movableElementsList.size(); i++)
           if ( m_movableElementsList[i] != NULL) delete &m_movableElementsList[i];
    */

    m_movableElementsList.clear();
}


/********************************************
    Getters
*********************************************
    Arthur : 21/02 - 25/02
    Florian: 21/02 - 25/02
*********************************************/
const MovableElement* Model::getPlayer() const { return m_player; }

int Model::getGameSpeed() const { return m_gameSpeed; }

unsigned long Model::getDistance() const { return m_totalDistance; }

std::set< MovableElement*> Model::getMEList() { return m_movableElementsList; }

std::vector< MovableElement*> Model::getNewMEList() { return m_newMovableElementsList; }
/*
std::set< MovableElement*> Model::getMEList() { return m_movableElementsList; }

std::set< MovableElement*> Model::getNewMEList() { return m_newMovableElementsList; }
*/


/********************************************
    Setters
*********************************************
    Arthur : 8/03 - 13/03
*********************************************/
void Model::setGameSpeed(int speed) { m_gameSpeed = speed; }
void Model::setCoinPickedUp() { m_nbCoinsPickedUp++;}


/********************************************
    Next Step
*********************************************
    Arthur : 21/02 - 8/03
*********************************************/
void Model::nextStep()
{
    float duration = (clock() - m_lastTime) / (double)CLOCKS_PER_SEC;
    if ( duration >= 0.100) // 100ms
    {
        m_totalDistance ++;

        //=== Add new enemies

        if (m_currentEnemyInterdistance == m_chosenEnemyInterdistance)
        {
            if (checkIfPositionFree(m_modelWidth, GAME_FLOOR) == true)
            {
                addNewMovableElement(m_modelWidth, GAME_FLOOR, 1);
                m_currentEnemyInterdistance = 0;
                chooseInterdistance(1);
            }
        }
        else
            m_currentEnemyInterdistance++;

        //=== Add new Coins

        if (m_currentCoinInterdistance == m_chosenCoinInterdistance)
        {
            if (checkIfPositionFree(m_modelWidth, GAME_FLOOR) == true)
            {
                addNewMovableElement(m_modelWidth, GAME_FLOOR-100, 2);
                m_currentCoinInterdistance = 0;
                chooseInterdistance(2);
            }
        }
        else
            m_currentCoinInterdistance++;


        m_lastTime = clock();
    }
}


/********************************************
    choose the interdistance between elements
*********************************************
    Arthur :  12/03 - 19/03
*********************************************/
void Model::chooseInterdistance(int elementType)
{
    //allows to calculate interdistance in different situations
    if  ( elementType  == 1 ) //enemy
    {
        if (m_chosenEnemyInterdistance > 40)
            m_chosenEnemyInterdistance = abs(rand()%30);
        else if  ( m_chosenEnemyInterdistance < 10)
            m_chosenEnemyInterdistance = abs(10 + rand()%40);
        else
            m_chosenEnemyInterdistance = abs(rand()%50);
    }

    else if ( elementType == 2 ) //coin
    {
        if (m_chosenCoinInterdistance > 20)
            m_chosenCoinInterdistance = abs(rand()%20);
        else if  ( m_chosenCoinInterdistance < 10)
            m_chosenCoinInterdistance = abs(15 + rand()%20);
        else
            m_chosenCoinInterdistance = abs(rand()%40);
    }
}


/********************************************
    check if a position is free to use
*********************************************
    Arthur :  8/03 - 19/03
*********************************************/
bool Model::checkIfPositionFree(const int posX, const int posY) const
{
    bool posFree=true;
    set<MovableElement*>::iterator it=m_movableElementsList.begin();

    while (posFree &&  it != m_movableElementsList.end() )
    {
        if ( (*it)->contains(posX, posY) )
            posFree = false;
        else
            ++it;
    }

    return posFree;
}


/********************************************
    NewMovableElement vector cleaning
*********************************************
    Arthur : 2/03- 2/03
    Florian: 2/03 - 2/03
*********************************************/
void Model::clearNewMovableElementList()
{
    m_newMovableElementsList.clear();
}


/********************************************
    Ball Moving
*********************************************
    Arthur : 21/02 - 6/03
    Florian: 21/02 - 2/03
*********************************************/
void Model::moveBallAccordingEvent(bool left)
{
    if (left)
        m_player->setPositionX( m_player->getPosX() - 10 );
    if (!left)
        m_player->setPositionX( m_player->getPosX() + 10 );
}


/********************************************
    Elements Moving (enemies, bonus, ...)
*********************************************
    Arthur : 6/03 - 19/03
*********************************************/
void Model::moveMovableElement(MovableElement *currentElement)
{
    assert(m_movableElementsList.find(currentElement) != m_movableElementsList.end() );
    currentElement->move();
}


/********************************************
    New MovableElement  Adding
*********************************************
    Arthur : 25/02 - 19/03
    Florian: 2/03 - 2/03
*********************************************/
void Model::addNewMovableElement(int posX, int posY, int type)
{
    if (type == 0)
    {
        m_player = new Ball(posX, posY, 30, 30, 0, 0);
        m_newMovableElementsList.push_back(m_player);
        m_movableElementsList.insert(m_player);
    }
    else if (type == 1)
    {
        Enemy *m_newEnemy = new Enemy(posX, posY, 30, 30, getGameSpeed()*(-1), 0);
        m_newMovableElementsList.push_back( m_newEnemy );
        m_movableElementsList.insert( m_newEnemy );
    }
    else if (type == 2)
    {
        Coin *m_newCoin = new Coin(posX, posY, 30, 30, getGameSpeed()*(-1), 0);
        m_newMovableElementsList.push_back( m_newCoin );
        m_movableElementsList.insert( m_newCoin );
    }

}


/********************************************
    Delete Movable Elements
    *********************************************
    Arthur : 12/03 - 19/03
    *********************************************/
void Model::deleteMovableElement(MovableElement *currentElement)
{
    assert(m_movableElementsList.find(currentElement) != m_movableElementsList.end() );
    m_movableElementsList.erase(m_movableElementsList.find(currentElement));
}
