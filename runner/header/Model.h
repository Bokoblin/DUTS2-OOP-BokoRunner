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
#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>

const int GAME_FLOOR = 480;
const int PLAYER_DEFAULT_POS_X = 50;


/********************************************
    Model Class
*********************************************
    Arthur : 21/02 - 12/03
    Florian: 21/02 - 2/03
*********************************************/
class Model
{
public:
    //=== CTORs / DTORs
    Model(int width, int height);
    ~Model();

    //=== GETTERS
    const MovableElement *getPlayer() const ;
    int getGameSpeed() const;
    unsigned long getDistance() const;
    std::vector<MovableElement *> getNewMEList();
    std::vector<MovableElement*> getMEList();

    //=== SETTERS
    void setGameSpeed(int speed);

    //=== METHODS
    void nextStep();
    void chooseInterdistance();
    bool checkIfPositionFree(const int posX, const int posY) const;
    void moveBallAccordingEvent(bool left);
    void moveMovableElement(MovableElement *currentElement,clock_t temps_DebutSaut);
    void deleteMovableElement(MovableElement *element);
    void addNewMovableElement(int posX, int posY, int type);
    void clearNewMovableElementList();

private:
    //=== ATTRIBUTES
    int m_modelWidth, m_modelHeight;
    unsigned long m_totalDistance;
    int  m_gameSpeed;
    //int m_currentInterdistance;
    //int  m_chosenInterdistanceBetweenEnnemies;

    Ball *m_player;

    //Dynamic arrays
    std::vector<MovableElement*> m_movableElementsList;
    std::vector<MovableElement*> m_newMovableElementsList;

public: //DEBUG ONLY
    int m_currentInterdistance;
    int  m_chosenInterdistance; //interdistance between elementss

};
#endif
