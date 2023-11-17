#include "Card.h"

using std::string;

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{
//------------------------------------------------
//          CONSTRUCTORS / DESTRUCTOR
//------------------------------------------------


/**
 * Constructs a card with coordinates,
 * a size and a context string
 *
 * @param x the x-axis coordinate
 * @param y the y-axis coordinate
 * @param width the width
 * @param height the height
 * @param context the context to make a contextual card
 *
 * @author Arthur
 * @date 06/07/2020
 */
Card::Card(float x, float y, float width, float height) :
        AbstractShapeMaterial(width, height, 999, 0)
{
    m_shape.setPosition(x, y);
    m_shape.setFillColor(m_fillColor); //FIXME:nope
    m_shape.setFillColor(m_outlineColor);
    Card::resize(width, height); //TODO: à faire dans le sync en ayant stocké la taille actuelle
}


//------------------------------------------------
//          GETTERS
//------------------------------------------------
float Card::getX() const {return m_shape.getPosition().x; }
float Card::getY() const {return m_shape.getPosition().y; }


//------------------------------------------------
//          SETTERS
//------------------------------------------------


//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Updates the card coloration
 * @author Arthur
 * @date 06/07/2020
 */
void Card::sync()
{
    AbstractShapeMaterial::sync(); // fixme default
}

/**
 * Draws the card (background and components)
 *
 * @param window the app's window
 *
 * @author Arthur
 * @date 06/07/2020
 */
void Card::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (isVisible()) {
        target.draw(m_shape, states);
    }
}

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin
