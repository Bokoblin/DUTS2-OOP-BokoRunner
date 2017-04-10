#include "GraphicElement.h"


/**
 * Constructs a GraphicElement with a size
 * @author Arthur
 * @date 21/02/16 - 10/04/17
 */
GraphicElement::GraphicElement(float width, float height) :
        m_width{width}, m_height{height}, m_isShowing{true}
{}


/**
 * Constructs a GraphicElement with
 * a position and a size
 * @author Arthur
 * @date 02/01/17 - 10/04/17
 */
GraphicElement::GraphicElement(float x, float y, float width, float height) :
        m_width{width}, m_height{height}, m_isShowing{true}
{
    this->setPosition(x, y);
}


/**
 * Constructs a GraphicElement with
 * a position, a size and an image
 * @author Arthur, Florian
 * @date 21/02/16 - 10/04/17
 */
GraphicElement::GraphicElement(float x, float y, float width, float height, const std::string &image) :
        m_width{width}, m_height{height}, m_isShowing{true}
{
    this->setPosition(x, y);
    setTextureFromImage(image);
}


/**
 * Copy Constructor
 * @author Arthur, Florian
 * @date 25/02/16 - 02/01/17
 */
GraphicElement::GraphicElement(GraphicElement const& element) :
    Sprite(), m_width(element.m_width), m_height(element.m_height), m_isShowing{element.m_isShowing}
{
    this->setPosition( element.getPosition() );
    this->setTexture( *element.getTexture(), true );
    this->setOrigin( element.getOrigin() );
}


/**
 * Destructor
 * @author Arthur, Florian
 * @date 21/02/16
 */
GraphicElement::~GraphicElement()
{}


//=== Getters
bool GraphicElement::isShowing() const { return m_isShowing; }

//=== Setters
void GraphicElement::show() { m_isShowing = true; }
void GraphicElement::hide() { m_isShowing = false; }


/**
 * Synchronization function
 * @author Arthur
 * @date 03/04/16
 */
void GraphicElement::sync()
{}


/**
 * Drawing function
 * @author Arthur
 * @date 30/03/16
 */
void GraphicElement::draw(sf::RenderWindow *window) const
{
    if (isShowing())
    {
        window->draw(*this);
    }
}


/**
 * Resizing function
 * @author Arthur
 * @date 22/02/16 - 25/02/16
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


/**
 * Sets the GraphicElement's texture from an image
 * @author Arthur
 * @date 02/01/17
 */
void GraphicElement::setTextureFromImage(std::string image)
{
    if (!m_texture.loadFromFile(image) )
        std::cerr << "ERROR when loading image file: " << image << std::endl;
    else
    {
        m_texture.setSmooth(true);
        setTexture(m_texture);
    }
}

/**
 * Sets the GraphicElement's texture from
 * a portion of an image
 * @author Arthur
 * @date 02/01/17
 */
void GraphicElement::setTextureFromImage(std::string image, sf::IntRect intRect) {
    if (!m_texture.loadFromFile(image, intRect) )
        std::cerr << "ERROR when loading image file: " << image << std::endl;
    else
    {
        m_texture.setSmooth(true);
        setTexture(m_texture);
    }
}


/**
 * Checks if a point of given coordinates is contained
 * inside this element
 * @author Arthur
 * @date 24/01/16
 */
bool GraphicElement::contains(float x, float y) const {
    return isShowing() && getGlobalBounds().contains(sf::Vector2f(x, y));
}
