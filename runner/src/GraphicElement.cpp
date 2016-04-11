#include "../header/GraphicElement.h"

/********************************************
    Parameterized Constructors
*********************************************
    @author Arthur  @date 21/02 - 03/04
    @author Florian @date 21/02 - 2/03
*********************************************/
GraphicElement::GraphicElement(sf::Texture &image, float x, float  y,
            float w, float h) : m_width{w}, m_height{h}
{
    this->setTexture(image);
    this->setPosition(x, y);
}

GraphicElement::GraphicElement( float w, float h) : m_width{w}, m_height{h}
{}


/********************************************
    Copy Constructor
*********************************************
    @author Arthur  @date 25/02 - 20/03
    @author Florian @date  2/03 - 2/03
*********************************************/
GraphicElement::GraphicElement(GraphicElement const& elementACopier) :
    Sprite(), m_width(elementACopier.m_width), m_height(elementACopier.m_height)
{
    this->setPosition( elementACopier.getPosition() );
    this->setTexture( *elementACopier.getTexture(), true );
    this->setOrigin( elementACopier.getOrigin() );
}


/********************************************
    Destructor
*********************************************
    @author Arthur  @date 21/02
    @author Florian @date 21/02
*********************************************/
GraphicElement::~GraphicElement()
{}


/********************************************
    Synchronization function
*********************************************
    @author Arhtur  @date 03/04
*********************************************/
void GraphicElement::sync()
{}


/********************************************
    Drawing function
*********************************************
    @author Arthur  @date 30/03
*********************************************/
void GraphicElement::draw(sf::RenderWindow *window) const
{
    window->draw(*this);
}


/********************************************
    Resizing function
*********************************************
    @author Arthur  @date 22/02 - 25/02
    @author Florian  @date 22/02
*********************************************/
void GraphicElement::resize(float width, float height)
{
    sf::FloatRect bb = this->getLocalBounds();
    float width_factor = width / bb.width;
    float height_factor = height / bb.height;
    this->setScale(width_factor, height_factor);
    //modification largeur et hauteur
    this->m_width = width;
    this->m_height = height;
}

