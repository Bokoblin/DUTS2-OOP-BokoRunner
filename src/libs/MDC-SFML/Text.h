/* Copyright 2016-2017 Jolivet Arthur & Laronze Florian

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

#ifndef TEXT_H
#define TEXT_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Config.h"

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

/**
 * Text Class inherited from sf::Text
 * @author Arthur
 * @date 21/12/16 - 29/12/17
 */
class Text : public sf::Text
{
public:
    //=== CTORs / DTORs
    explicit Text(const std::string &description);
    Text(const std::string &description, bool isVisible);

    //=== GETTERS
    std::string getDescription() const;
    bool isVisible() const;

    //=== SETTERS
    void setDescription(const std::string &description);
    void setPositionSelfCentered(double x, double y);
    void setStringFromInt(int value);
    void setVisible(bool on);

    //=== METHODS
    void draw(sf::RenderWindow *window) const;
    bool contains(float posX, float posY) const;
    void applyTextFont(const std::string &fontFileName, unsigned int charSize, sf::Color color);

private:
    //=== ATTRIBUTES
    sf::Font m_font;
    std::string m_description;
    bool m_isVisible;
};

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin

#endif
