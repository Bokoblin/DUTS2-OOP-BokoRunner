/* Copyright 2016-2019 Jolivet Arthur & Laronze Florian

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

#include "app/model/utils/RandomUtils.h"
#include "app/model/enums/MovableElementType.h"

/**
 * @class MovableElement
 * @note Abstract class
 * @details Provide common attributes and methods
 * to inherited classes
 *
 * @author Arthur, Florian
 * @date 23/02/2016 - 11/07/2019
 */
class MovableElement
{
public:
    //=== CTORs / DTORs
    MovableElement(float posX, float posY, float w, float h, float mvX, float mvY);
    virtual ~MovableElement();

    //=== METHODS
    virtual void move() = 0;
    bool contains(float x, float y) const;
    bool collide(const MovableElement& other);

    //=== GETTERS
    float getPosX() const;
    float getPosY() const;
    float getWidth() const;
    float getHeight() const;
    bool isColliding() const;
    virtual MovableElementType getType() const;

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
