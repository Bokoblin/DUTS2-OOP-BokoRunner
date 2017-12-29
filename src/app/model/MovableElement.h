/* Copyright 2016-2017 Jolivet Arthur & Laronze Florian

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef MOVABLE_ELEMENT_H
#define MOVABLE_ELEMENT_H

#include "../utils/RandomUtils.h"
#include "../enum/MovableElementType.h"

/**
 * The MovableElement class is an abstract class
 * providing common attributes and methods
 * to inherited Movable Elements
 * @author Arthur, Florian
 * @date 23/02/16 - 18/05/16
 */
class MovableElement
{
public:
    //=== CTORs / DTORs
    MovableElement(float posX, float posY, float w, float h, float mvX, float mvY);
    virtual ~MovableElement();

    //=== METHODS
    virtual void move()=0;
    bool contains(float posX, float posY) const ;
    bool collision(const MovableElement &other) const ;

    //=== GETTERS
    float getPosX() const;
    float getPosY() const;
    float getWidth() const;
    float getHeight() const;
    bool isColliding() const;
    virtual MovableElementType getType() const;

    //=== SETTERS
    void setMoveX(float mvX);
    void setMoveY(float mvY);
    void setColliding(bool on);

protected:
    //=== ATTRIBUTES
    float m_posX;
    float m_posY;
    float m_width;
    float m_height;
    float m_moveX;
    float m_moveY;
    bool m_isColliding;
    MovableElementType m_elementType;
};

#endif
