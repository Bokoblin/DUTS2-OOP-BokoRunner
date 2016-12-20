#include "GraphicElement.h"

/**
 * Parameterized Constructors
 * @author Arthur, Florian
 * @date 21/02 - 03/04
 */
GraphicElement::GraphicElement(sf::Texture &image, float x, float y,
            float w, float h) : m_width{w}, m_height{h}
{
    this->setTexture(image);
    this->setPosition(x, y);
}

GraphicElement::GraphicElement( float w, float h) : m_width{w}, m_height{h}
{}


/**
 * Copy Constructor
 * @author Arthur, Florian
 * @date 25/02 - 20/03
 */
GraphicElement::GraphicElement(GraphicElement const& element) :
    Sprite(), m_width(element.m_width), m_height(element.m_height)
{
    this->setPosition( element.getPosition() );
    this->setTexture( *element.getTexture(), true );
    this->setOrigin( element.getOrigin() );
}


/**
 * Destructor
 * @author Arthur, Florian
 * @date 21/02
 */
GraphicElement::~GraphicElement()
{}


/**
 * Synchronization function
 * @author Arthur
 * @date 03/04
 */
void GraphicElement::sync()
{}


/**
 * Drawing function
 * @author Arthur
 * @date 30/03
 */
void GraphicElement::draw(sf::RenderWindow *window) const
{
    window->draw(*this);
}


/**
 * Resizing function
 * @author Arthur
 * @date 22/02 - 25/02
 */
void GraphicElement::resize(float width, float height)
{
    sf::FloatRect bb = this->getLocalBounds();
    float width_factor = width / bb.width;
    float height_factor = height / bb.height;
    this->setScale(width_factor, height_factor);
    this->m_width = width;
    this->m_height = height;
}

