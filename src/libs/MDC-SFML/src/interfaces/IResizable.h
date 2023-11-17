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

#ifndef MDC_SFML_RESIZABLE_H
#define MDC_SFML_RESIZABLE_H

#include <SFML/System/Vector2.hpp>

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

/**
 * @interface IResizable
 * @details Defines resize related feature
 *
 * @author Arthur
 * @date 28/06/2020 - 05/07/2020
 *
 * @see sf::Vector2f
 */
class IResizable
{
public:
    //=== DTOR
    virtual ~IResizable() = default;

    //=== GETTERS
    virtual const sf::Vector2f& getOriginalSize() const = 0;
    virtual const sf::Vector2f& getSize() = 0; //Note: not const due to calculation in some classes
    virtual float getWidth() const = 0;
    virtual float getHeight() const = 0;

    //=== METHODS
    virtual void resize(const sf::Vector2f& size) = 0;
    virtual void resize(float width = -1, float height = -1) = 0; //FIXME: default params are allegedly prohibited

    //=== STATES
    const unsigned int NEED_RESIZE = 1131331490;
};

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin

#endif
