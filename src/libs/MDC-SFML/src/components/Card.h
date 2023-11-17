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

#ifndef MDC_SFML_CARD_H
#define MDC_SFML_CARD_H

#include <functional>
#include <SFML/Graphics/Sprite.hpp>
#include "../components/Text.h"
#include "../components/AbstractShapeMaterial.h"
#include "../utils/LabelPosition.h"

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

/**
 * @class Card
 * @inherit AbstractShapeMaterial
 * @implements IPositionable, ISynchronizable
 * @details TODO
 *
 *
 *
 * @author Arthur
 * @date 05/07/2020
 *
 * @see AbstractTexturedMaterial
 * @see IPositionable
 */
class Card: public AbstractShapeMaterial
{
public:
    //=== CTORs / DTORs
    Card(float x, float y, float width, float height);
    virtual ~Card() = default;
//    Image(float x, float y, float width, float height, const std::string& textureFile = "");
//    Image(Image const& other);
//    ~Image() override = default;
//
//    //=== GETTERS
    float getX() const override;
    float getY() const override;
//
//    //=== SETTERS
//    void setOrigin(float x, float y) override; //FIXME
//    void setPosition(float x, float y) override; //FIXME
//
//    //=== METHODS
    void sync() override;
    //bool contains(const sf::Vector2f& position) const override; //FIXME
//    void resize(const sf::Vector2f& size) override;
//
protected:
    //=== METHODS
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
//    void processTextureLoading(const std::string& file) override;
//
//    //=== ATTRIBUTES
//    sf::Sprite m_sprite;
};

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin

#endif
