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

//=======================================
// Constructeurs
//=======================================
Model::Model(int width, int height)
    :  m_modelWidth(width), m_modelHeight(height)
{
    m_player = new Ball();
    m_movableElementsList.push_back(m_player);
}

//=======================================
// Destructeurs
//=======================================
Model::~Model()
{
    if(m_player!= NULL)
        delete m_player;

    for(unsigned int i=0; i<m_movableElementsList.size(); i++)
        delete m_movableElementsList[i];
}

//=======================================
// Calcul la prochaine étape
//=======================================
void Model::nextStep()
{
    int alea = rand()%m_modelWidth;

    for(unsigned int i=0; i<m_movableElementsList.size(); i++)
    {
        m_movableElementsList[i]->setPositionX(alea);
    }
}

//=======================================
// Accesseurs en lecture
//=======================================

Ball Model::getBall() const
{
    return *m_player;
}

const MovableElement* Model::getMovBall() const
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

//=======================================
// Deplacement Ball
//=======================================
void Model::moveBall(bool left)
{
    if (left)
        m_player->setPositionX( m_player->getPosX() - m_player->getMoveX() );
    if (!left)
        m_player->setPositionX( m_player->getPosX() + m_player->getMoveX() );
}

//=======================================
// Ajout de nouveaux éléments
//=======================================
void Model::addNewElement()
{
    MovableElement *me = new MovableElement();
    m_newMovableElementsList.push_back( me );
    m_movableElementsList.push_back( me );


    cout << "=== Contenu m_element===" << endl;
    for(unsigned int i=0; i<m_movableElementsList.size(); i++)
    {
        cout << m_movableElementsList[i] << endl;
    }
}
