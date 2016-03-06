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
#include <vector>

/********************************************
    Model Class
*********************************************
    Arthur : 21/02 - 6/03
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
    std::vector<MovableElement *> getNewMEList();
    std::vector<MovableElement*> getMEList();

    //=== METHODS
    void nextStep();
    void moveBallAccordingEvent(bool left);
    void moveElements();
    void addBallMovableElement();
    void addNewMovableElement();
    void clearNewMovableElementList();

private:
    //=== ATTRIBUTES
    int m_modelWidth, m_modelHeight;
    Ball *m_player;

    //Dynamic arrays
    std::vector<MovableElement*> m_movableElementsList;
    std::vector<MovableElement*> m_newMovableElementsList;
};
#endif
