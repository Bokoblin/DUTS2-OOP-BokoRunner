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

#ifndef _MODEL_H
#define _MODEL_H

#include "Ball.h"
#include "Enemy.h"
#include "Coin.h"
#include <cstdlib>
#include <iostream>
#include <set>
#include <vector>
#include <cassert>
#include <ctime>

const int GAME_FLOOR = 470;
const int PLAYER_DEFAULT_POS_X = 50 ;

/********************************************
    Model Class
*********************************************
    Arthur : 21/02 - 23/03
    Florian: 21/02 - 2/03
*********************************************/
class Model
{
public:
    //=== CTORs / DTORs
    Model(int width, int height);
    ~Model();

    //=== GETTERS
    bool getIntroState() const;
    bool getMenuState() const;
    bool getGameState() const;
    MovableElement* getPlayer() const;
    int getScore() const;
    int getDistance() const;
    int getGameSpeed() const;
    const std::set<MovableElement*>& getNewMElementsArray();
    const std::set<MovableElement*>& getMElementsArray();

    //=== SETTERS
    void setIntroState(bool state);
    void setMenuState(bool state);
    void setGameState(bool state);
    void setGameSpeed(int speed);
    void setCoinPickedUp() ;

    //=== METHODS
    void nextStep();
    void chooseInterdistance(int elementType);
    bool checkIfPositionFree(const int posX, const int posY) const;
    void moveBallAccordingEvent(bool left);
    void moveMovableElement(MovableElement *element);
    void deleteMovableElement();
    void addANewMovableElement(int posX, int posY, int type);
    void clearNewMovableElementList();

private:
    //=== ATTRIBUTES
    int m_modelWidth, m_modelHeight;
    int m_introState;
    int m_menuState;
    int m_gameState;
    int m_score;
    int m_totalDistance;
    int m_gameSpeed;
    time_t m_lastTime;
    int m_nbCoinsPickedUp;
    int m_currentEnemyInterdistance;
    int m_currentCoinInterdistance;
    int m_chosenEnemyInterdistance;
    int m_chosenCoinInterdistance;

    MovableElement *m_player;
    MovableElement *m_newMElement;

    //Containers
    std::set<MovableElement*> m_movableElementsArray;
    std::set<MovableElement*> m_newMovableElementsArray;

};

#endif
