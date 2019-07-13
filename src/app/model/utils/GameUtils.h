/* Copyright 2017-2019 Jolivet Arthur

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

#ifndef GAME_UTILS_H
#define GAME_UTILS_H

#include "../enums/MovableElementType.h"
#include "RandomUtils.h"

#define repeat(_n) for (int i = 0; i < _n;i++)

/**
 * @class GameUtils
 * @details Provide utils functions for the GameModel class
 *
 * @author Arthur
 * @date 06/09/2018
 */
class GameUtils
{
public:
/**
 * Calculates the minimal distance between two elements
 * for the next to spawn
 *
 * @param nextElementSpawnDistance the next spawn distance for this element
 * @param elementType the type of element that was just created
 * @return the minimal spawn distance
 *
 * @author Arthur
 * @date 12/03/2016 - 06/09/2018
 */
    static int chooseSpawnDistance(int nextElementSpawnDistance, int elementType)
    {
        int spawnDistance = 0;

        switch (elementType) {
            case STANDARD_ENEMY: //Any enemy though
            {
                if (nextElementSpawnDistance > 40) {
                    spawnDistance = RandomUtils::getUniformRandomNumber(0, 30); //Between 0 and 30 meters
                } else if (nextElementSpawnDistance < 10) {
                    spawnDistance = RandomUtils::getUniformRandomNumber(10, 50); //Between 10 and 50 meters
                } else {
                    spawnDistance = RandomUtils::getUniformRandomNumber(0, 40); //Between 0 and 40 meters
                }
            }
                break;
            case COIN: {
                if (nextElementSpawnDistance > 10) {
                    spawnDistance = RandomUtils::getUniformRandomNumber(0, 10); //0 to 10m
                } else if (nextElementSpawnDistance < 10) {
                    spawnDistance = RandomUtils::getUniformRandomNumber(10, 20); //10 to 20m
                } else {
                    spawnDistance = RandomUtils::getUniformRandomNumber(0, 20); //0 to 20m
                }
            }
                break;
            case PV_PLUS_BONUS: //Any bonus though
            {
                if (nextElementSpawnDistance > 300) {
                    spawnDistance = RandomUtils::getUniformRandomNumber(200, 300); //200 to 300m
                } else if (nextElementSpawnDistance < 275) {
                    spawnDistance = RandomUtils::getUniformRandomNumber(300, 400);  //300 to 400m
                } else {
                    spawnDistance = RandomUtils::getUniformRandomNumber(200, 400); //200 to 400m
                }
            }
                break;
            default:
                break;
        }

        return spawnDistance;
    }
};

#endif
