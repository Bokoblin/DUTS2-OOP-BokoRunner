/* Copyright 2016-2020 Jolivet Arthur

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

#ifndef MDC_SFML_RADIO_BUTTON_H
#define MDC_SFML_RADIO_BUTTON_H

#include "AbstractStateButton.h"

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

/**
 * The RadioButton Class inherited from AbstractStateButton class
 * is an 8-state button that can be selected (one at a time in a group).
 * It supports a feature-packed preconfigured "radio" texture and supports a label.
 *
 * Provided image files must comport 8 tiles of the following format:
 * ENABLED_SELECTED_UNPRESSED   ENABLED_SELECTED_PRESSED
 * ENABLED_UNPRESSED            ENABLED_PRESSED
 * DISABLED_SELECTED_UNPRESSED  DISABLED_SELECTED_PRESSED
 * DISABLED_UNPRESSED           DISABLED_SELECTED
 *
 * @author Arthur
 * @date 23/12/2016 - 02/05/2020
 *
 * @see AbstractStateButton
 */
class RadioButton: public AbstractStateButton
{
public:
    //=== CTORs / DTORs
    RadioButton(float x, float y, float origDiameter, float newDiameter,
                const std::string& label = "",
                const std::string& customImage = Config::RADIO_BUTTON_IMAGE,
                LabelPosition labelPosition = RIGHT,
                bool isSelected = false);
    RadioButton(const RadioButton& other);
    ~RadioButton() override = default;

    //=== GETTERS
    bool isSelected() const;

    //=== SETTERS
    void setSelected(bool selected);

    //=== METHODS
    void syncLabelPosition() override;
};

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin

#endif
