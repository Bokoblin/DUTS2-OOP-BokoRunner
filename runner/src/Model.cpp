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
    m_chosenInterdistanceBetweenEnnemies = 100;
}


/********************************************
    Destructor
*********************************************
    Arthur : 21/02 - 5/03
    Florian: 21/02 - 2/03
*********************************************/
Model::~Model()
{
    if(m_player!= NULL)
        delete m_player;

    for(auto it=m_movableElementsList.begin(); it!=m_movableElementsList.end(); ++it)
    {
        if (*it!=NULL)
            delete *it;
    }

    m_movableElementsList.clear();
}


/********************************************
    Getters
*********************************************
    Arthur : 21/02 - 25/02
    Florian: 21/02 - 25/02
*********************************************/
const MovableElement* Model::getBallElement() const { return m_player; }

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

    //=== Add new ennemies

    if (m_currentInterdistance == m_chosenInterdistanceBetweenEnnemies)
    {
        if (checkPositionFree(m_modelWidth, 480) == true)
        {
            addNewMovableElement(m_modelWidth, 480);
            m_currentInterdistance = 0;
            chooseInterdistance();
        }
    }
    else
    {
        m_currentInterdistance++;
    }


// TODO (ARTHUR#1#): create different ennemies in add newMovableElement (add a sub class ennemies ???)

}


/********************************************
    choose the interdistance between element
*********************************************
    Arthur :  12/03
*********************************************/
void Model::chooseInterdistance()
{
    //allows to calculate interdistance in different situations
    if (m_chosenInterdistanceBetweenEnnemies > 100)
        m_chosenInterdistanceBetweenEnnemies = abs(rand()%150 - 50);
    else if  ( m_chosenInterdistanceBetweenEnnemies < 25)
    {
        m_chosenInterdistanceBetweenEnnemies = abs(30 + rand()%100);
    }
    else
        m_chosenInterdistanceBetweenEnnemies = abs(rand()%150);
}




/********************************************
    check if a position is free to add an element
*********************************************
    Arthur :  8/03 - 12/03
*********************************************/
bool Model::checkPositionFree(const int posX, const int posY) const
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
    Elements Moving (ennemies, bonus, points)
*********************************************
    Arthur : 6/03 - 6/03
*********************************************/
void Model::moveElements()
{
    for (unsigned int i=0; i < m_movableElementsList.size(); i++  )
    {
        if ( m_movableElementsList[i]->getType() != 0)
            m_movableElementsList[i]->move();
        else
            m_player->move();
    }
}


/********************************************
    Ball Adding
*********************************************
    Arthur : 5/03 - 6/03
*********************************************/
void Model::addBallMovableElement()
{
    m_player = new Ball(50, 480, 30, 30);
    m_movableElementsList.push_back(m_player);
    m_newMovableElementsList.push_back(m_player);
}


/********************************************
    NewMovableElement  Adding
*********************************************
    Arthur : 25/02 - 12/03
    Florian: 2/03 - 2/03
*********************************************/
void Model::addNewMovableElement(int posX, int posY)
{
    MovableElement *newMovElem = new MovableElement(posX, posY, 30, 30,-4, 0, 1);
    m_newMovableElementsList.push_back( newMovElem );
    m_movableElementsList.push_back( newMovElem );
}


/********************************************
    Delete MovableElements
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
