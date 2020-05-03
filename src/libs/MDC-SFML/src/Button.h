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

#ifndef MDC_SFML_BUTTON_H
#define MDC_SFML_BUTTON_H

#include "LabelPosition.h"
#include "Sprite.h"
#include "Text.h"
#include <functional>

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

/**
 * The Button class inherits Sprite.
 * It implements button components such as press states and a label. \n
 * It is possible to choose the label position (following 5 positions)
 * and to update it using a string file thanks to its description (i.e. id)
 *
 * @author Arthur
 * @date 06/04/16 - 03/05/2020
 *
 * @see Sprite
 * @see LabelPosition
 */
class Button: public Sprite
{
public:
    //=== CTORs / DTORs
    Button(float x, float y, float width, float height,
           const std::string& description = "",
           const std::string& textureImage = "");
    Button(Button const& other);
    ~Button() override = default;

    //=== FUNCTION POINTERS
    typedef std::function<std::string(const std::string& label)> label_retrieval_func_t;

    //=== GETTERS
    bool isPressed() const;
    bool isEnabled() const;
    LabelPosition getLabelPosition() const;

    //=== SETTERS
    virtual void setPressed(bool pressed);
    void setEnabled(bool enabled);
    void setPositionSelfCentered(float x, float y);
    void setLabelDescription(const std::string& description);
    virtual void setLabelPosition(const LabelPosition& labelPosition);

    //=== METHODS
    void sync() override;
    virtual void retrieveLabel(const label_retrieval_func_t& func);
    virtual void syncLabelPosition();
    void draw(sf::RenderWindow* window) const override;
    bool contains(float x, float y) const override;

protected:
    //=== ATTRIBUTES
    bool m_isPressed;
    bool m_isEnabled;
    sf::Font m_font;
    Text m_label;
    LabelPosition m_labelPosition;

    //Constants
    const unsigned int DEFAULT_CHAR_SIZE = 22;
    const float HORIZONTAL_LABEL_MARGIN = 30;
};

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin

#endif
