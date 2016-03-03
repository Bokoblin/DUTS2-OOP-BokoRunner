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
#include "../header/Ball.h"

using namespace std;


/********************************************
    Parameterized Constructor
*********************************************
    Arthur : 21/02 - 2/03
    Florian: 21/02 - 2/03
*********************************************/
Model::Model(int width, int height)
    :  m_modelWidth(width), m_modelHeight(height)
{
    m_player = new Ball(50, 450, 25, 25, 10, 10); //temp location
    m_movableElementsList.push_back(m_player);
}

/********************************************
    Destructor
*********************************************
    Arthur : 21/02 - 2/03
    Florian: 21/02 - 2/03
*********************************************/
Model::~Model()
{
    if(m_player!= NULL)
        delete m_player;
/*
    for(auto it=m_movableElementsList.begin(); it!=m_movableElementsList.end(); ++it)
    {
        if (*it!=NULL)
            delete *it; //causes a sigaborted
    }
*/
    m_movableElementsList.clear();
}

/********************************************
    Next Step Calcul
*********************************************
    Arthur : 21/02 - 25/02
*********************************************/
void Model::nextStep()
{
    int alea = rand()%m_modelWidth;

    for(unsigned int i=0; i<m_movableElementsList.size(); i++)
    {
        m_movableElementsList[i]->setPositionX(alea);
    }
}

/********************************************
    New MovableElement vector cleaning
*********************************************
    Arthur : 2/03- 2/03
    Florian: 2/03 - 2/03
*********************************************/
void Model::clearNewMovableElementVector()
{
        m_newMovableElementsList.clear();
}


/********************************************
    Getters
*********************************************
    Arthur : 21/02 - 25/02
    Florian: 21/02 - 25/02
*********************************************/
const MovableElement* Model::getBallElement() const
{
    return m_player;
}

std::vector< MovableElement*> Model::getMovableElementsList()
{
    return m_movableElementsList;
}

std::vector< MovableElement*> Model::getNewMovableElementsList()
{
    return m_newMovableElementsList;
}

/********************************************
    Ball Moving
*********************************************
    Arthur : 21/02 - 2/03
    Florian: 21/02 - 2/03
*********************************************/
void Model::moveBall(bool left)
{
    if (left)
        m_player->setPositionX( m_player->getPosX() - m_player->getMoveX() );
    if (!left)
        m_player->setPositionX( m_player->getPosX() + m_player->getMoveX() );
}

/********************************************
    New MovableElement instance adding
*********************************************
    Arthur : 25/02 - 2/03
    Florian: 2/03 - 2/03
*********************************************/
void Model::addNewMovableElement()
{
    MovableElement *newMovElem = new MovableElement(rand()%800, 450, 20, 20,-10, 0);
    m_newMovableElementsList.push_back( newMovElem );
    m_movableElementsList.push_back( newMovElem );
}
