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

#ifndef MDC_SFML_TOGGLE_BUTTON_H
#define MDC_SFML_TOGGLE_BUTTON_H

#include "Button.h"
#include "Sprite.h"

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

/**
 * The ToggleButton Class inherited from Button class
 * is a two-state button with two display clips.
 *
 * The label shall only be on the left or the right.
 * Providing top, center or bottom position can lead to unexpected behavior.
 *
 * Provided image files must comport 8 tiles of the following format:
 * ENABLED_TOGGLED_UNPRESSED    ENABLED_TOGGLED_PRESSED
 * ENABLED_UNPRESSED            ENABLED_PRESSED
 * DISABLED_TOGGLED_UNPRESSED   DISABLED_TOGGLED_PRESSED
 * DISABLED_UNPRESSED           DISABLED_SELECTED
 *
 * @author Arthur
 * @date 28/04/2020
 *
 * @see Button
 */
class ToggleButton: public Button
{
public:
    //=== CTORs / DTORs
    ToggleButton(float x, float y, float width, float height,
                 const std::string& label = "",
                 const std::string& customImage = Config::TOGGLE_BUTTON_IMAGE);
    ToggleButton(const ToggleButton& other);
    ~ToggleButton() override = default;

    //=== GETTERS
    bool isToggled() const;

    //=== SETTERS
    void setToggled(bool toggled);

    //=== METHODS
    void sync() override;
    void syncLabelPosition() override;
    void setLabelPosition(const LabelPosition& labelPosition) override;

protected:
    //=== ATTRIBUTES
    bool m_isToggled;
    const float HORIZONTAL_LABEL_MARGIN = 20;
};

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin

#endif
