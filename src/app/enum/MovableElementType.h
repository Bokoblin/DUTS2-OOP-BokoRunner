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

#ifndef MOVABLE_ELEMENT_TYPE_H
#define MOVABLE_ELEMENT_TYPE_H

/**
 * The MovableElementType enum defines the different
 * types of MovableElement available in the game.
 * @author Arthur
 * @date 30/01/17
 */
enum MovableElementType
{
    PLAYER,
    STANDARD_ENEMY,
    TOTEM_ENEMY,
    BLOCK_ENEMY,
    COIN,
    PV_PLUS_BONUS,
    MEGA_BONUS,
    FLY_BONUS,
    SLOW_SPEED_BONUS,
    SHIELD_BONUS,
    UNDEFINED
};

#endif
