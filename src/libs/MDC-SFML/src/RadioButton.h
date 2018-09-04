/* Copyright 2016-2018 Jolivet Arthur

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

#include "Button.h"
#include "Sprite.h"

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

/**
 * The RadioButton Class inherited from Button class
 * adds different syncing behaviours
 * a pre-configured texture with its clip rectangles
 * and a different label location than other buttons.
 *
 * @author Arthur
 * @date 23/12/16 - 04/01/18
 *
 * @see Button
 */
class RadioButton : public Button
{
public:
    //=== CTORs / DTORs
    RadioButton(float x, float y, float diameter);
    RadioButton(float x, float y, float diameter, const std::string &description);
    RadioButton(const RadioButton& other);
    ~RadioButton() override;

    //=== GETTERS
    bool isSelected() const;

    //=== SETTERS
    void setSelected(bool selected);

    //=== METHODS
    void sync() override;
    void syncLabelPosition() override;
    void setLabelPosition(LabelPosition labelPosition) override; //TOP, CENTER and BOTTOM are unexpected behaviours

protected:
    //=== ATTRIBUTES
    bool m_isSelected;

    //=== METHODS
    void setRadioClipRect();

    //=== CONSTANTS
    const std::string RADIO_BUTTONS_IMAGE = "../res/images/ui/radio_buttons.png";
    const std::string INDICATOR_IMAGE = "../res/images/ui/indicator_buttons.png"; //TODO: split RADIO BUTTON FROM PAGE BUTTON (TBD)
};

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin

#endif
