#include "AbstractShapeMaterial.h"

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{
//------------------------------------------------
//          CONSTRUCTORS / DESTRUCTOR
//------------------------------------------------
/**
 * Constructs with a size and an optional image
 *
 * @param width the width
 * @param height the height
 * @param image the image used for the texture (optional)
 *
 * @author Arthur
 * @date 21/02/2016 - 28/06/2020
 */
AbstractShapeMaterial::AbstractShapeMaterial(float width, float height, int depth, float radius) :
        AbstractMaterial(width, height, depth)
{
    m_shape = sf::CircleShape(radius);
}

/**
 * Copy Constructor
 *
 * @param other another button object to copy
 *
 * @author Arthur, Florian
 * @date 25/02/2016 - 28/06/2020
 */
AbstractShapeMaterial::AbstractShapeMaterial(AbstractShapeMaterial const& other) :
        AbstractMaterial(other), m_shape{other.m_shape} {}

/**
 * TODO
 * 6/07
 */
void AbstractShapeMaterial::sync()
{
    m_shape.setFillColor(m_fillColor);
    m_shape.setOutlineColor(m_outlineColor);
}

void AbstractShapeMaterial::setOrigin(float x, float y)
{
    m_shape.setOrigin(x, y);
}

void AbstractShapeMaterial::setPosition(float x, float y)
{
    m_shape.setPosition(x, y);
}

bool AbstractShapeMaterial::contains(const sf::Vector2f& position) const
{
    return m_shape.getGlobalBounds().contains(position); //fixme: global or local
}

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin
