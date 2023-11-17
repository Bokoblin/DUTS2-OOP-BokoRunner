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

#ifndef MDC_SFML_ABSTRACT_STATE_BUTTON_H
#define MDC_SFML_ABSTRACT_STATE_BUTTON_H

#include "Button.h"
#include <SFML/Graphics/Color.hpp>

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

/**
 * @class AbstractStateButton
 * @inherit Button
 * @details It represents a button that can hold a state
 * (other than being pressed) through rectangle clips.
 * The following states are available : pressed, checked, enabled. \n
 * The rectangle clips are used to adapt rendering following states. \n
 *
 * The label shall only be on the left or the right.
 * Providing top, center or bottom position can lead to unexpected behavior.
 *
 * @author Arthur
 * @date 03/05/2020
 *
 * @see Button
 */
class AbstractStateButton: public Button
{
public:
    //=== METHODS
    void sync() override;

    //=== SETTERS
    void setLabelPosition(const LabelPosition& labelPosition) override;

protected:
    //=== CTORs / DTORs
    AbstractStateButton(float x, float y, float oldWidth, float oldHeight, float newWidth, float newHeight,
                        const std::string& label = "",
                        const std::string& customImage = Config::RADIO_BUTTON_IMAGE,
                        LabelPosition labelPosition = RIGHT,
                        bool isChecked = false);
    AbstractStateButton(const AbstractStateButton& other);
    ~AbstractStateButton() override = default;

    //=== ATTRIBUTES
    std::vector<sf::IntRect> m_clipRectArray;
    unsigned int m_currentClipRect;
    const float HORIZONTAL_LABEL_MARGIN = 20;

    //=== STATES
    const unsigned int CHECKED = 2798434082;
};

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin

#endif
