/* Copyright 2016 Jolivet Arthur & Laronze Florian

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

#ifndef ENEMY_H
#define ENEMY_H

#include "MovableElement.h"


/********************************************
    Enemy Class
*********************************************
    @author Arthur  @date 13/03 - 11/04
*********************************************/
class Enemy : public MovableElement
{
public:
    //=== CTORs / DTORs
    Enemy(float x, float y, float w, float h, float mvX, float mvY);
    virtual~Enemy();

    //=== METHODS
    void move();
    void chooseEnemyType();

};

#endif // ENEMY_H
