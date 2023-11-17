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

#ifndef MDC_SFML_ABSTRACT_SHAPE_MATERIAL_H
#define MDC_SFML_ABSTRACT_SHAPE_MATERIAL_H

#include <SFML/Graphics/CircleShape.hpp>
#include "AbstractMaterial.h"
#include "../interfaces/IPositionable.h"
#include "../interfaces/ISynchronizable.h"

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

/**
 * TODO
 *
 * @author Arthur
 * @date 28/06/2020
 *
 * @see AbstractMaterial
 */
class AbstractShapeMaterial: public AbstractMaterial, public IPositionable, public ISynchronizable
{
public:
    //=== CTORs / DTORs
    virtual ~AbstractShapeMaterial() override = default;

    //=== SETTERS
    void setOrigin(float x, float y) override;
    void setPosition(float x, float y) override;

    //=== METHODS
    bool contains(const sf::Vector2f &position) const override;
    void sync() override;

protected:
    //=== CTORs / DTORs
    AbstractShapeMaterial(float width, float height, int depth = 0, float radius = 0);
    AbstractShapeMaterial(AbstractShapeMaterial const& other);

    //=== ATTRIBUTES
    sf::CircleShape m_shape; //TODO: maybe shall be private to avoid wrong operations
};

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin

#endif
