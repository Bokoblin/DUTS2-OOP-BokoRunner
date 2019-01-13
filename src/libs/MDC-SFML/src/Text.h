/* Copyright 2016-2019 Jolivet Arthur

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
#include "Config.h"

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

/**
 * The Text class inherits sf::Text.
 * It adds visibility, a text description (i.e. identifier) and a font tied to the text.
 *
 * @author Arthur
 * @date 21/12/16 - 13/01/19
 *
 * @see sf::Text
 */
class Text : public sf::Text
{
public:
    //=== CTORs / DTORs
    explicit Text(const std::string &description);
    Text(const std::string &description, bool isVisible);
    Text(const Text& other);

    //=== GETTERS
    virtual float getWidth() const;
    virtual float getHeight() const;
    std::string getDescription() const;
    bool isVisible() const;

    //=== SETTERS
    void setDescription(const std::string &description);
    void setPositionSelfCentered(float x, float y);
    void setStringFromInt(int value);
    void setUtf8String(const std::string &content);
    void setVisible(bool visible);

    //=== METHODS
    void draw(sf::RenderWindow *window) const;
    bool contains(float x, float y) const;
    void applyTextFont(const std::string& fontFileName, unsigned int charSize, const sf::Color& color);

private:
    //=== ATTRIBUTES
    sf::Font m_font;
    std::string m_description;
    bool m_isVisible;
};

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin

#endif
