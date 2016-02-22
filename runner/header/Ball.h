/*
Copyright (C) 2015 Jolivet Arthur & Laronze Florian

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

#ifndef BALL_H
#define BALL_H

class Ball
{
    public:
        //ATTRIBUTS
        Ball();
        Ball(int m_posX, int m_posY, int m_width, int m_height, int m_moveX, int m_moveY);
        ~Ball();

        //METHODES
        move();

        //ACCESSEURS
        int getMoveX();
        int getMoveY();
        int getPositionX();
        int getPositionY();

        void setPositionX(int x);
        void setPositionY(int y);



    protected:

    private:
        int m_posX;
        int m_posY;
        int m_width;
        int m_height;
        int m_moveX;
        int m_moveY;
};

#endif // BALL_H
