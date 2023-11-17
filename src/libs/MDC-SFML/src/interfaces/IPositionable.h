/* Copyright 2020 Jolivet Arthur

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

#ifndef MDC_SFML_POSITIONABLE_H
#define MDC_SFML_POSITIONABLE_H

#include <SFML/System/Vector2.hpp>

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

/**
 * @interface IPositionable
 * @implements sf::Drawable
 * @details Defines position-related methods
 *
 * @author Arthur
 * @date 28/06/2020 - 05/07/2020
 *
 * @see sf::Vector2f
 */
class IPositionable
{
public:
    //=== DTOR
    virtual ~IPositionable() = default;

    //=== GETTERS
    virtual float getX() const = 0;
    virtual float getY() const = 0;

    //=== SETTERS
    virtual void setOrigin(float x, float y) = 0; //FIXME: temporary?
    virtual void setPosition(float x, float y) = 0; //FIXME: temporary?

    //=== METHODS
    virtual bool contains(const sf::Vector2f& position) const = 0;
};

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin

#endif
