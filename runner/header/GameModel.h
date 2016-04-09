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

#ifndef _GAMEMODEL_H
#define _GAMEMODEL_H

#include "Model.h"
#include "Player.h"
#include "Enemy.h"
#include "Coin.h"
#include <cstdlib>
#include <iostream>
#include <set>
#include <cassert>

const unsigned int PLAYER_DEFAULT_POS_X = 50 ;

/********************************************
    GameModel Class
*********************************************
    Arthur : 26/03 - 01/04
*********************************************/
class GameModel : public Model
{
public:
    //=== CTORs / DTORs
    GameModel(unsigned int width, unsigned int height, std::chrono::system_clock::time_point programBegginingTime);
    ~GameModel();

    //=== GETTERS
    bool getPauseState() const;
    bool getEndState() const;
    Player* getPlayer() const;
    int getScore() const;
    int getDistance() const;
    int getGameSpeed() const;
    unsigned int getNbCoinsCollected() const;
    const std::set<MovableElement*>& getNewMElementsArray();
    const std::set<MovableElement*>& getMElementsArray();

    //=== SETTERS
    void setPauseState(bool state);
    void setEndState(bool state);
    void setGameSpeed(int speed);
    void setNbCoinsCollected(unsigned int number) ;

    //=== METHODS
    virtual void nextStep() override;
    void chooseInterdistance(int elementType);
    bool checkIfPositionFree(const unsigned int posX, const unsigned int posY) const;
    void moveBallAccordingEvent(bool left);
    void moveMovableElement(MovableElement *element);
    void deleteMovableElement();
    void addANewMovableElement(float posX, float posY, int type);
    void clearNewMovableElementList();

private:
    //=== ATTRIBUTES

    bool m_pauseState;
    bool m_endState;
    int m_score;
    int m_distance;
    int m_gameSpeed;
    std::chrono::system_clock::time_point m_lastTime;
    int m_nbCoinsCollected;
    int m_currentEnemyInterdistance;
    int m_currentCoinInterdistance;
    int m_chosenEnemyInterdistance;
    int m_chosenCoinInterdistance;

    Player *m_player;
    MovableElement *m_newMElement;

    //Containers
    std::set<MovableElement*> m_movableElementsArray;
    std::set<MovableElement*> m_newMovableElementsArray;

};

#endif
