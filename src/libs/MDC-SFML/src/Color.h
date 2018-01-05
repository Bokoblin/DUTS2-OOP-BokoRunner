/* Copyright 2017-2018 Jolivet Arthur

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

#ifndef MDC_SFML_COLOR_H
#define MDC_SFML_COLOR_H

#include <SFML/Graphics/Color.hpp>

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

/**
 * The Color class inherits sf::Color.
 * It defines the official Material colors that can be found
 * at @code https://material.io/guidelines/style/color.html.
 * It also defines custom colors.
 *
 * @author Arthur
 * @date 29/12/17 - 04/01/2018
 *
 * @see sf::Color
 */
class Color: public sf::Color
{
public:
    //=== ATTRIBUTES

    //Main colors
    static const sf::Color MaterialRed;
    static const sf::Color MaterialPink;
    static const sf::Color MaterialPurple;
    static const sf::Color MaterialDeepPurple;
    static const sf::Color MaterialIndigo;
    static const sf::Color MaterialBlue;
    static const sf::Color MaterialLightBlue;
    static const sf::Color MaterialCyan;
    static const sf::Color MaterialTeal;
    static const sf::Color MaterialGreen;
    static const sf::Color MaterialLightGreen;
    static const sf::Color MaterialLime;
    static const sf::Color MaterialYellow;
    static const sf::Color MaterialAmber;
    static const sf::Color MaterialOrange;
    static const sf::Color MaterialDeepOrange;
    static const sf::Color MaterialBrown;
    static const sf::Color MaterialGrey;
    static const sf::Color MaterialBlueGrey;

    //Additional colors
    static const sf::Color MaterialGreenA700;
};

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin

#endif
