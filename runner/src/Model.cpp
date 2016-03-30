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
    Arthur : 21/02 - 26/03
    Florian: 21/02 - 2/03
*********************************************/
Model::Model(int width, int height, const chrono::_V2::system_clock::time_point beginTime)  :
    m_width(width), m_height(height), m_programBeginningTime{beginTime}
{
    m_introState = true;
    m_menuState = false;
    m_gameState = false;
}


/********************************************
    Destructor
*********************************************
    Arthur : 21/02 - 26/03
    Florian: 21/02 - 2/03
*********************************************/
Model::~Model()
{
}


/********************************************
    Getters
*********************************************
    Arthur : 21/02 - 26/03
    Florian: 21/02 - 25/02
*********************************************/
bool Model::getIntroState() const {return m_introState;}
bool Model::getMenuState() const {return m_menuState;}
bool Model::getGameState() const {return m_gameState;}
std::chrono::system_clock::time_point Model::getProgramBeginningTime() const { return m_programBeginningTime; }



/********************************************
    Setters
*********************************************
    Arthur : 8/03 - 26/03
*********************************************/
void Model::setIntroState(bool state) {m_introState = state;}
void Model::setMenuState(bool state) {m_menuState = state;}
void Model::setGameState(bool state) {m_gameState = state;}



/********************************************
    Next Step
*********************************************
    Arthur : 21/02 - 27/03
*********************************************/
void Model::nextStep()
{ }
