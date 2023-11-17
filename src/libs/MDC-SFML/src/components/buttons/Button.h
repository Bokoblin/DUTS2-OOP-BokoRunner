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

#include <functional>
#include <SFML/Graphics/Sprite.hpp>
#include "../../components/AbstractTexturedMaterial.h"
#include "../../components/Text.h"
#include "../../interfaces/IPositionable.h"
#include "../../interfaces/ISynchronizable.h"
#include "../../utils/LabelPosition.h"

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
 * @date 06/04/2016 - 01/07/2020
 *
 * @see AbstractTexturedMaterial
 * @see IActionable, IPositionable, ISynchronizable
 * @see LabelPosition
 */
class Button: public AbstractTexturedMaterial, public IActionable, IPositionable, ISynchronizable
{
public:
    //=== CTORs / DTORs
    Button(float x, float y, float width, float height,
           const LabelPosition& labelPosition = CENTER,
           const std::string& description = "",
           const std::string& textureFile = "");
    Button(Button const& other);
    ~Button() override = default;

    //=== FUNCTION POINTERS
    typedef std::function<std::string(const std::string& label)> label_retrieval_func_t;

    //=== GETTERS
    bool isClicked() const override;
    bool isEnabled() const override;
    bool isHovered() const override;
    bool isPressed() const override;
    float getX() const override;
    float getY() const override;

    //=== SETTERS
    void setClicked(bool value = true) override;
    void setEnabled(bool value = true) override;
    void setHovered(bool value = true) override;
    void setPressed(bool value = true) override;
    void setOrigin(float x, float y) override;
    void setPosition(float x, float y) override;
    void setLabelDescription(const std::string& description);
    virtual void setLabelPosition(const LabelPosition& labelPosition);

    //=== METHODS
    bool contains(const sf::Vector2f& position) const override;
    void resize(const sf::Vector2f& size) override;
    void resize(float width, float height) override;
    void resize(float size) ; //FIXMe: compat
    void sync() override;

    virtual void retrieveLabel(const label_retrieval_func_t& func);
    virtual void syncLabelPosition();

protected:
    //=== METHODS
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void processTextureLoading(const std::string& file) override;

    //=== ATTRIBUTES
    sf::Sprite m_buttonSprite;
    sf::Font m_font;
    Text m_label;
    LabelPosition m_labelPosition;

    //Constants
    const unsigned int DEFAULT_CHAR_SIZE = 22;
    const float HORIZONTAL_LABEL_MARGIN = 30;

    //=== STATES
    const unsigned int NEED_LABEL_SYNC = 2179507182;
};

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin

#endif
