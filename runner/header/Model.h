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

#include <cstdlib>
#include <iostream>
#include <cassert>
#include <chrono>

/********************************************
    Model Class
*********************************************
    Arthur : 21/02 - 26/03
    Florian: 21/02 - 2/03
*********************************************/
class Model
{
public:
    //=== CTORs / DTORs
    Model(int width, int height, const std::chrono::system_clock::time_point beginTime);
    ~Model();

    //=== GETTERS
    bool getIntroState() const;
    bool getMenuState() const;
    bool getGameState() const;
    bool getPauseState() const;
    std::chrono::system_clock::time_point getProgramBeginningTime() const ;

    //=== SETTERS
    void setIntroState(bool state);
    void setMenuState(bool state);
    void setGameState(bool state);
    void setPauseState(bool state);

    //=== METHODS
    virtual void nextStep();

protected:
    //=== ATTRIBUTES
    int m_width, m_height;
    bool m_introState;
    bool m_menuState;
    bool m_gameState;
    bool m_pauseState;
    const std::chrono::system_clock::time_point m_programBeginningTime;
};

#endif
