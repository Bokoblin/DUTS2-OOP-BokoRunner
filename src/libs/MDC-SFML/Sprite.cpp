#include "Sprite.h"

using std::string;
using Bokoblin::SimpleLogger::Logger;

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

//------------------------------------------------
//          CONSTRUCTORS / DESTRUCTOR
//------------------------------------------------

/**
 * Constructs a GraphicElement with a size
 * @author Arthur
 * @date 21/02/16 - 24/12/17
 */
Sprite::Sprite(float width, float height) :
        m_width{width}, m_height{height}, m_isShowing{true},
        m_alpha{255}, m_light{255}, m_texture_filename{""}
{}


/**
 * Constructs a GraphicElement with
 * a position and a size
 * @author Arthur
 * @date 02/01/17 - 24/12/17
 */
Sprite::Sprite(float x, float y, float width, float height) :
        Sprite(width, height)
{
    this->setPosition(x, y);
}


/**
 * Constructs a GraphicElement with
 * a position, a size and an image
 * @author Arthur, Florian
 * @date 21/02/16 - 24/12/17
 */
Sprite::Sprite(float x, float y, float width, float height, const string &image) :
        Sprite(x, y, width, height)
{
    setTextureFromImage(image);
}


/**
 * Copy Constructor
 * @author Arthur, Florian
 * @date 25/02/16 - 27/12/17
 */
Sprite::Sprite(Sprite const& other) :
        sf::Sprite(), m_width(other.m_width), m_height(other.m_height),
        m_isShowing{other.m_isShowing}, m_alpha{other.m_alpha}, m_light{other.m_light},
        m_texture_filename{other.m_texture_filename}
{
    this->setPosition(other.getPosition());
    this->setTexture(*other.getTexture(), true);
    this->setOrigin(other.getOrigin());
}


/**
 * Destructor
 * @author Arthur, Florian
 * @date 21/02/16
 */
Sprite::~Sprite() = default;


//------------------------------------------------
//          GETTERS
//------------------------------------------------

float Sprite::getWidth() const { return m_width; };
float Sprite::getHeight() const { return m_height; };
bool Sprite::isVisible() const { return m_isShowing; }
int Sprite::getAlpha() const { return m_alpha; }
int Sprite::getLight() const { return m_light; }
string Sprite::getTextureFileName() const { return m_texture_filename; }


//------------------------------------------------
//          SETTERS
//------------------------------------------------

void Sprite::show() { m_isShowing = true; }
void Sprite::hide() { m_isShowing = false; }
void Sprite::setAlpha(int alpha)
{
    if (alpha < 0)
        m_alpha = 0;
    else if (alpha > 255)
        m_alpha = 255;
    else
        m_alpha = (sf::Uint8) alpha;
}
void Sprite::setLight(int light)
{
    if (light < 0)
        m_light = 0;
    else if (light > 255)
        m_light = 255;
    else
        m_light = (sf::Uint8) light;
}
void Sprite::increaseAlpha(int alphaLevel) { setAlpha(getAlpha() + alphaLevel); }
void Sprite::decreaseAlpha(int alphaLevel) { setAlpha(getAlpha() - alphaLevel); }
void Sprite::increaseLight(int lightLevel) { setLight(getLight() + lightLevel); }
void Sprite::decreaseLight(int lightLevel) { setLight(getLight() - lightLevel); }


//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Synchronization function
 * @author Arthur
 * @date 03/04/16 - 24/12/17
 */
void Sprite::sync()
{
    applyColor();
}


/**
 * Drawing function
 * @author Arthur
 * @date 30/03/16
 */
void Sprite::draw(sf::RenderWindow *window) const
{
    if (isVisible())
    {
        window->draw(*this);
    }
}


/**
 * Resizing function
 * @author Arthur
 * @date 22/02/16 - 25/02/16
 */
void Sprite::resize(float width, float height)
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
 * @date 02/01/17 - 29/12/17
 */
void Sprite::setTextureFromImage(const string &image)
{
    if (!m_texture.loadFromFile(image))
    Logger::printErrorOnConsole("Image loading failed for \"" + image + "\"");
    else
    {
        m_texture.setSmooth(true);
        setTexture(m_texture);
        m_texture_filename = image;
    }
}

/**
 * Sets the GraphicElement's texture from
 * a portion of an image
 * @author Arthur
 * @date 02/01/17 - 29/12/17
 */
void Sprite::setTextureFromImage(const string &image, sf::IntRect intRect) {
    if (!m_texture.loadFromFile(image, intRect))
        Logger::printErrorOnConsole("Image loading failed for \"" + image + "\"");
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
bool Sprite::contains(float x, float y) const {
    return isVisible() && getGlobalBounds().contains(sf::Vector2f(x, y));
}


/**
 * Apply light and alpha values to color
 * @author Arthur
 * @date 24/12/17
 */
void Sprite::applyColor()
{
    setColor(sf::Color(m_light, m_light, m_light, m_alpha));
}

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin
