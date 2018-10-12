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

#ifndef MDC_SFML_RAISED_BUTTON_H
#define MDC_SFML_RAISED_BUTTON_H

#include "Button.h"
#include <SFML/Graphics/Color.hpp>

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

/**
 * The RaisedButton class inherits Button.
 * It represents a raised button: a button
 * which shrink when pressed
 *
 * @author Arthur
 * @date 12/09/18 - 12/10/18
 *
 * @see Button
 */
class RaisedButton : public Button
{
public:
    //=== CTORs / DTORs
    RaisedButton(float x, float y, float width, float height);
    RaisedButton(float x, float y, float width, float height, const std::string& label,
                 const std::string& customImage = Config::RAISED_BUTTON_IMAGE);
    RaisedButton(RaisedButton const& other);
    ~RaisedButton() override;

    //=== SETTERS
    void setPressed(bool pressed) override;

    //=== METHODS
    void resize(float width, float height) override;
    void resize(float size) override;
    void sync() override;
    void syncLabelPosition() override;

protected:
    //=== ATTRIBUTES
    sf::Vector2f m_initialPos;
    sf::Vector2f m_initialScale;
};

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin

#endif
