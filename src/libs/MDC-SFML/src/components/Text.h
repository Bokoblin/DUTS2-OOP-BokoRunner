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

#ifndef MDC_SFML_TEXT_H
#define MDC_SFML_TEXT_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../components/AbstractMaterial.h"
#include "../interfaces/IPositionable.h"
#include "../utils/Config.h"

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

/**
 * @class Text
 * @inherit AbstractMaterial
 * @implements IPositionable
 * @details Defines a text element with an identifier (description) and a font
 *
 * @author Arthur
 * @date 21/12/2016 - 28/06/2020
 *
 * @see sf::Text
 */
class Text: public AbstractMaterial, public IPositionable
{
public:
    //=== CTORs / DTORs
    Text(const std::string& description, bool isVisible = "");
    Text(const Text& other);

    //=== GETTERS
    float getX() const override;
    float getY() const override;
    float getWidth() const override;
    float getHeight() const override;
    std::string getDescription() const;
    /**@deprecated*/ unsigned int getCharacterSize() const; //FIXME: Temp for compatibility

    //=== SETTERS
    /**@deprecated*/ void setFont(const sf::Font& font); //FIXME: Temp for compatibility
    /**@deprecated*/ void setCharacterSize(unsigned int size); //FIXME: Temp for compatibility
    /**@deprecated*/ void setStyle(int size); //FIXME: Temp for compatibility
    /**@deprecated*/ void setString(const std::string& content); //FIXME: Temp for compatibility
    /**@deprecated*/ void setOrigin(float x, float y) override; //FIXME: Temp for compatibility
    /**@deprecated*/ void setPosition(float x, float y); //FIXME: Temp for compatibility
    void setDescription(const std::string& description);
    void setPositionSelfCentered(float x, float y);
    void setStringFromInt(int value);
    void setUtf8String(const std::string& content);

    //=== METHODS
    bool contains(const sf::Vector2f& position) const override;
    void applyTextFont(const std::string& fontFileName,
                       unsigned int charSize = 14,
                       const sf::Color& color = sf::Color::White);

protected:
    //=== METHODS
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    //=== ATTRIBUTES
    sf::Text m_text;
    sf::Font m_font;
    std::string m_description;
};

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin

#endif
