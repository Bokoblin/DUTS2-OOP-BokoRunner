/* Copyright 2018 Jolivet Arthur

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

#ifndef APP_COLOR_H
#define APP_COLOR_H

#include <SFML/Graphics/Color.hpp>
#include "libs/MDC-SFML/src/Color.h"

namespace mdsf = Bokoblin::MaterialDesignComponentsForSFML;

/**
 * The AppColor class defines custom colors used in the app.
 *
 * @author Arthur
 * @date 05/01/2018
 */
class AppColor
{
public:
    //=== ATTRIBUTES
    static const sf::Color CoalMine;
    static const sf::Color CoinGold;
    static const sf::Color EnemyBlue;
    static const sf::Color ScoreGrey;
    static const sf::Color URLRed;
};

#endif
