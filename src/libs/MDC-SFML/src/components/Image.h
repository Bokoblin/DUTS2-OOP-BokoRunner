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

#ifndef MDC_SFML_IMAGE_H
#define MDC_SFML_IMAGE_H

#include <functional>
#include <SFML/Graphics/Sprite.hpp>
#include "AbstractTexturedMaterial.h"
#include "Text.h"
#include "../interfaces/IPositionable.h"
#include "../interfaces/ISynchronizable.h"
#include "../utils/LabelPosition.h"

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

/**
 * TODO
 *
 * @author Arthur
 * @date 01/07/2020
 *
 * @see AbstractTexturedMaterial
 * @see IPositionable
 */
class Image: public AbstractTexturedMaterial, public IPositionable, public ISynchronizable
{
public:
    //=== CTORs / DTORs
    Image(float width, float height, const std::string& textureFile = "");
    Image(float x, float y, float width, float height, const std::string& textureFile = "");
    Image(Image const& other);
    ~Image() override = default;

    //=== GETTERS
    float getX() const override;
    float getY() const override;

    //=== SETTERS
    void setOrigin(float x, float y) override;
    void setPosition(float x, float y) override; //FIXME
    void setTextureRect(const sf::IntRect&) ;

    //=== METHODS
    bool contains(const sf::Vector2f& position) const override;
    void resize(const sf::Vector2f& size) override;
    void resize(float width, float height) override; //FIXME
    void resize(float size); //FIXME
    void sync() override;

protected:
    //=== METHODS
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void processTextureLoading(const std::string& file) override;

    //=== ATTRIBUTES
    sf::Sprite m_sprite;
};

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin

#endif
