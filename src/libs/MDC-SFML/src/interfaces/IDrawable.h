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

#ifndef MDC_SFML_DRAWABLE_H
#define MDC_SFML_DRAWABLE_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>
#include "../utils/Color.h"

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

/**
 * @interface IDrawable
 * @implements sf::Drawable
 * @details Defines visibility and color modifier features.
 *
 * @author Arthur
 * @date 28/06/2020 - 05/07/2020
 *
 * @see Color, sf::Color
 */
class IDrawable: public sf::Drawable
{
public:
    //=== DTOR
    virtual ~IDrawable() = default;

    //=== GETTERS
    virtual bool isVisible() const = 0;
    virtual int getAlpha() const = 0;
    virtual int getLight() const = 0;
    virtual int getDepth() const = 0;

    //=== SETTERS
    virtual void setVisible(bool visible = true) = 0;
    virtual void setAlpha(int value, Color::Modifier = Color::REPL) = 0;
    virtual void setLight(int value, Color::Modifier = Color::REPL) = 0;
    virtual void setFillColor(const sf::Color& color) = 0;
    virtual void setOutlineColor(const sf::Color& color) = 0;

    //=== STATES
    const unsigned int VISIBLE = 1290281003;
};

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin

#endif
