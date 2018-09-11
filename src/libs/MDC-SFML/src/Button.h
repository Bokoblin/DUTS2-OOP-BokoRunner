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

#ifndef MDC_SFML_BUTTON_H
#define MDC_SFML_BUTTON_H

#include "LabelPosition.h"
#include "Sprite.h"
#include "Text.h"

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

/**
 * The Button class inherits Sprite.
 * It implements button components such as states, rectangle clips and a label. \n
 * The following states are available : pressed, selected, enabled. \n
 * The rectangle clips are used to adapt rendering following states. \n
 * It is possible to choose the label position (following 5 positions)
 * and to update it using a string file thanks to its description (i.e. id)
 *
 * @author Arthur
 * @date 06/04/16 - 02/01/18
 *
 * @see Sprite
 * @see LabelPosition
 */
class Button: public Sprite
{
public:
    //=== CTORs / DTORs
    Button(float x, float y, float width, float height);
    Button(float x, float y, float width, float height, const std::string& description);
    Button(float x, float y, float width, float height, const std::string& textureImage,
           const std::vector<sf::IntRect>& clipRect);
    Button(float x, float y, float width, float height, const std::string& description,
           const std::string& textureImage, const std::vector<sf::IntRect>& clipRect);
    Button(Button const& other);
    ~Button() override;

    //=== FUNCTION POINTERS
    typedef std::string (* label_retrieval_func_t)(const std::string& label);

    //=== GETTERS
    bool isPressed() const;
    bool isEnabled() const;
    LabelPosition getLabelPosition() const;

    //=== SETTERS
    void setPressed(bool pressed);
    void setEnabled(bool enabled);
    void setClipRectArray(std::vector<sf::IntRect> array);
    void setPositionSelfCentered(float x, float y);
    void setLabelDescription(const std::string& description);
    virtual void setLabelPosition(LabelPosition labelPosition);

    //=== METHODS
    void sync() override;
    virtual void retrieveLabel(label_retrieval_func_t func);
    virtual void syncLabelPosition();
    virtual void retrieveAndSyncLabel(label_retrieval_func_t func);
    void draw(sf::RenderWindow* window) const override;
    bool contains(float x, float y) const override;

protected:
    //=== ATTRIBUTES
    std::vector<sf::IntRect> m_clipRectArray;
    unsigned int m_currentClipRect;
    bool m_isPressed;
    bool m_isEnabled;
    sf::Font m_font;
    Text m_label;
    LabelPosition m_labelPosition;

    //Constants
    const int DEFAULT_CHAR_SIZE = 22;
};

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin

#endif
