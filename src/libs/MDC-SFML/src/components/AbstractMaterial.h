/* Copyright 2016-2020 Jolivet Arthur & Laronze Florian

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

#ifndef MDC_SFML_ABSTRACT_MATERIAL_H
#define MDC_SFML_ABSTRACT_MATERIAL_H

#include <map>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "../interfaces/IActionable.h"
#include "../interfaces/IDrawable.h"
#include "../interfaces/IResizable.h"
#include "../utils/Color.h"
#include "../utils/Config.h"

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

/**
 * The AbstractMaterial class implements IDrawable and IResizable.
 * It defines visibility and color control as a drawable material. \n
 *
 * @author Arthur, Florian
 * @date 21/02/2016 - 28/06/2020
 *
 * @see IDrawable, IResizable
 */
class AbstractMaterial: public IDrawable, public IResizable
{
public:
    //=== CTORs / DTORs
    virtual ~AbstractMaterial() = default;

    //=== GETTERS
    bool isVisible() const override;
    int getAlpha() const override;
    int getLight() const override;
    int getDepth() const override;
    const sf::Vector2f& getOriginalSize() const override;
    const sf::Vector2f& getSize() override;
    float getWidth() const override;
    float getHeight() const override;

    //=== SETTERS
    void setVisible(bool visible = true) override;
    void setAlpha(int value, Color::Modifier = Color::REPL) override;
    void setLight(int value, Color::Modifier = Color::REPL) override;
    void setFillColor(const sf::Color& color) override;
    void setOutlineColor(const sf::Color& color) override;

    //=== METHODS
    void resize(const sf::Vector2f& size) override;
    void resize(float width = -1, float height = -1) override;

protected:
    //=== CTORs / DTORs
    AbstractMaterial(float width, float height, int depth = 0);
    AbstractMaterial(AbstractMaterial const& other);

    //=== ATTRIBUTES
    sf::Uint8 m_alpha;
    sf::Uint8 m_light;
    int m_depth;
    sf::Vector2f m_initialSize;
    sf::Vector2f m_size;
    sf::Color m_fillColor;
    sf::Color m_outlineColor;
    std::map<int, bool> m_states;

private:
    //=== METHODS
    void applyColor(sf::Color target, sf::Color source);
};

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin

#endif
