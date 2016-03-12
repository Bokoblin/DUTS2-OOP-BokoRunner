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
#include <cstdlib>
#include <iostream>
#include <vector>

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
    const MovableElement *getBallElement() const ;
    int getGameSpeed() const;
    unsigned long getDistance() const;
    std::vector<MovableElement *> getNewMEList();
    std::vector<MovableElement*> getMEList();

    //=== SETTERS
    void setGameSpeed(int speed);

    //=== METHODS
    void nextStep();
    void chooseInterdistance();
    bool checkPositionFree(const int posX, const int posY) const;
    void moveBallAccordingEvent(bool left);
    void moveElements();
    void deleteMovableElement(MovableElement *element);
    void addBallMovableElement();
    void addNewMovableElement(int posX, int posY);
    // TODO (ARTHUR#1#): Merge addElements functions ?

    void clearNewMovableElementList();

private:
    //=== ATTRIBUTES
    int m_modelWidth, m_modelHeight;
    unsigned long m_totalDistance;
    //int m_currentInterdistance;
    int  m_gameSpeed;
    //int  m_chosenInterdistanceBetweenEnnemies;

    Ball *m_player;

    //Dynamic arrays
    std::vector<MovableElement*> m_movableElementsList;
    std::vector<MovableElement*> m_newMovableElementsList;

public: //DEBUG ONLY
    int m_currentInterdistance;
    int  m_chosenInterdistanceBetweenEnnemies;

};
#endif
