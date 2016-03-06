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

/********************************************
    Parameterized Constructor
*********************************************
    Arthur : 21/02 - 2/03
    Florian: 21/02 - 2/03
*********************************************/
Model::Model(int width, int height)
    :  m_modelWidth(width), m_modelHeight(height)
{

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
    Next Step Calcul
*********************************************
    Arthur : 21/02 - 6/03
*********************************************/
void Model::nextStep()
{
    //no usage for the moment
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
    Getters
*********************************************
    Arthur : 21/02 - 25/02
    Florian: 21/02 - 25/02
*********************************************/
const MovableElement* Model::getBallElement() const { return m_player; }

std::vector< MovableElement*> Model::getMEList() { return m_movableElementsList; }

std::vector< MovableElement*> Model::getNewMEList() { return m_newMovableElementsList; }


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
        if ( m_movableElementsList[i] != m_player)
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
    Arthur : 25/02 - 2/03
    Florian: 2/03 - 2/03
*********************************************/
void Model::addNewMovableElement()
{
    MovableElement *newMovElem = new MovableElement(m_modelWidth, 480, 30, 30,-4, 0);
    m_newMovableElementsList.push_back( newMovElem );
    m_movableElementsList.push_back( newMovElem );
}
