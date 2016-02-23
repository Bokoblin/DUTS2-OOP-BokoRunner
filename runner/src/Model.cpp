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
#include <iostream>
#include <fstream>
using namespace std;

//=======================================
// Constructeurs
//=======================================
Model::Model(int width, int height)
    :  m_modelWidth(width), m_modelHeight(height)
{
    m_player = new Ball();
}

//=======================================
// Destructeurs
//=======================================
Model::~Model()
{
    if(m_player!= NULL)
        delete m_player;
}

//=======================================
// Calcul la prochaine étape
//=======================================
void Model::nextStep()
{
//    for_each(m_listElements.begin(), m_listElements.end(),)

//Modifier la méthode nextStep() du modèle afin qu'elle déplace
// de manière aléatoire les objets mobiles.
}

//=======================================
// Accesseurs en lecture
//=======================================

Ball Model::getBall()
{
    return *m_player;
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

