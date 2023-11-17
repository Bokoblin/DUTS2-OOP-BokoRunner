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

#ifndef MDC_SFML_ABSTRACT_TEXTURED_MATERIAL_H
#define MDC_SFML_ABSTRACT_TEXTURED_MATERIAL_H

#include <SFML/Graphics/Texture.hpp>
#include "AbstractMaterial.h"

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

/**
 * TODO
 * The Sprite class inherits sf::Sprite.
 * It adds visibility, alpha and light percentage control to a sprite. \n
 * It keeps the texture (and its filename) used to set sprite texture
 * for sync purpose in inherited classes.
 * Finally, it allows resize and position containing check.
 *
 * @author Arthur
 * @date 28/06/2020
 *
 * @see AbstractMaterial
 */
class AbstractTexturedMaterial: public AbstractMaterial
{
public:
    //=== CTORs / DTORs
    virtual ~AbstractTexturedMaterial() override = default;

    //=== METHODS
    void loadAndApplyTextureFromFile(const std::string& file, const sf::IntRect& area = sf::IntRect());

protected:
    //=== CTORs / DTORs
    AbstractTexturedMaterial(float width, float height, const std::string& image = "");
    AbstractTexturedMaterial(AbstractTexturedMaterial const& other);

    //=== ATTRIBUTES
    sf::Texture m_texture;
    std::string m_textureFilename;

    //=== METHODS
    virtual void processTextureLoading(const std::string& file);
};

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin

#endif
