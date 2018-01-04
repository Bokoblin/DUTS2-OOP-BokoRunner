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

#ifndef Color_H
#define Color_H

#include <SFML/Graphics/Color.hpp>

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

/**
 * The Color class inherits sf::Color.
 * It defines other colors used by MDC-SFML.
 *
 * @author Arthur
 * @date 29/12/17
 *
 * @see sf::Color
 */
class Color: public sf::Color
{
public:
    //=== ATTRIBUTES
    static const sf::Color MaterialTeal;
    static const sf::Color MaterialMine;
};

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin

#endif
