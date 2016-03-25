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
    m_currentInterdistance = 0;
    m_chosenInterdistance = 100;
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

std::vector< MovableElement*> Model::getMEList() { return m_movableElementsList; }

std::vector< MovableElement*> Model::getNewMEList() { return m_newMovableElementsList; }


/********************************************
    Setters
*********************************************
    Arthur : 8/03 - 8/03
*********************************************/
void Model::setGameSpeed(int speed) { m_gameSpeed = speed; }



/********************************************
    Next Step
*********************************************
    Arthur : 21/02 - 8/03
*********************************************/
void Model::nextStep()
{
    m_totalDistance ++;


    //if( m_player->getPosY() == GAME_FLOOR)
      //  m_player->setJumpState(false);

    //=== Add new enemies

    if (m_currentInterdistance == m_chosenInterdistance)
    {
        if (checkIfPositionFree(m_modelWidth, GAME_FLOOR) == true)
        {
            addNewMovableElement(m_modelWidth, GAME_FLOOR, 1);
            m_currentInterdistance = 0;
            chooseInterdistance();
        }
    }
    else
    {
        m_currentInterdistance++;
    }
}


/********************************************
    choose the interdistance between element
*********************************************
    Arthur :  12/03
*********************************************/
void Model::chooseInterdistance()
{
    //allows to calculate interdistance in different situations
    if (m_chosenInterdistance > 100)
        m_chosenInterdistance = abs(rand()%150 - 50);
    else if  ( m_chosenInterdistance < 25)
    {
        m_chosenInterdistance = abs(30 + rand()%100);
    }
    else
        m_chosenInterdistance = abs(rand()%150);
}


/********************************************
    check if a position is free to use
*********************************************
    Arthur :  8/03 - 12/03
*********************************************/
bool Model::checkIfPositionFree(const int posX, const int posY) const
{
    bool posFree=true;
    unsigned int i = 0;
    while (posFree && i < m_movableElementsList.size() )
    {
        if (m_movableElementsList[i]->contains(posX, posY) )
            posFree = false;
        else
            i++;
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
    Arthur : 6/03 - 13/03
*********************************************/
void Model::moveMovableElement(MovableElement *currentElement)
{
    currentElement->move();
}


/********************************************
    New MovableElement  Adding
*********************************************
    Arthur : 25/02 - 13/03
    Florian: 2/03 - 2/03
*********************************************/
void Model::addNewMovableElement(int posX, int posY, int type)
{
    if (type == 0)
    {
        m_player = new Ball(posX, posY, 30, 30, 1, 1);
        m_movableElementsList.push_back(m_player);
        m_newMovableElementsList.push_back(m_player);
    }
    else if (type == 1)
    {
        Enemy *m_newEnemy = new Enemy(posX, posY, 30, 30,getGameSpeed()*(-1), 0);
        m_newMovableElementsList.push_back( m_newEnemy );
        m_movableElementsList.push_back( m_newEnemy );
    }
}


/********************************************
    Delete Movable Elements
    *********************************************
    Arthur : 12/03
    *********************************************/
void Model::deleteMovableElement(MovableElement *element)
{
    std::vector<MovableElement*>::iterator it = m_movableElementsList.begin();
    bool trouve = false;
    while (!trouve && it != m_movableElementsList.end() )
    {
        if (*it == element)
        {
            m_movableElementsList.erase(it);
            trouve=true;
        }
        else
            it++;
    }
}


