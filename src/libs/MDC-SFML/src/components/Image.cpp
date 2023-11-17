#include "Image.h"

using std::string;

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{
//------------------------------------------------
//          CONSTRUCTORS / DESTRUCTOR
//------------------------------------------------
//TODO: add clip rect parameter for allowing non-states clips to regroup images
// (to introduce with image DB (filename + origin + original size))

/**
 * @brief Constructs a Image with coordinates,
 * a size, a texture and an image rectangle clip
 *
 * @param x the x-axis coordinate
 * @param y the y-axis coordinate
 * @param width the width
 * @param height the height
 * @param textureFile the Image texture image (optional)
 *
 * @author Arthur
 * @date 06/07/2020
 */
Image::Image(float x, float y, float width, float height, const string& textureFile) :
        Image(width, height, textureFile)
{
    m_sprite.setPosition(x, y);
}

Image::Image(float width, float height, const string& textureFile) :
        AbstractTexturedMaterial(width, height, textureFile) {}

/**
 * @brief Copy Constructor
 *
 * @param other another Image object to copy
 *
 * @author Arthur
 * @date 06/04/2016 - 06/07/2020
 */
Image::Image(Image const& other) :
        AbstractTexturedMaterial(other)
{
    m_sprite.setPosition(other.m_sprite.getPosition());
    m_sprite.setTexture(*other.m_sprite.getTexture(), true); //NOTE: Can be problematic
    m_sprite.setOrigin(other.m_sprite.getOrigin());
    m_sprite.setColor(other.m_sprite.getColor());
}

//------------------------------------------------
//          GETTERS
//------------------------------------------------
float Image::getX() const { return m_sprite.getPosition().x; }

float Image::getY() const { return m_sprite.getPosition().y; }

//------------------------------------------------
//          SETTERS
//------------------------------------------------

//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * @brief Checks if a point of given coordinates is contained
 * in the Image or its label
 *
 * @param x the x-axis coordinate
 * @param y the y-axis coordinate
 *
 * @author Arthur
 * @date 06/07/2020
 */
bool Image::contains(const sf::Vector2f& position) const
{
    return isVisible() && (m_sprite.getGlobalBounds().contains(position));
}

/**
 * Resizes the Image using sprite scaling
 *
 * @param size the new size
 *
 * @author Arthur
 * @date 06/07/2020
 */
void Image::resize(const sf::Vector2f& size)
{
    float width_factor = size.x / getOriginalSize().x;
    float height_factor = size.y / getOriginalSize().y;
    m_sprite.setScale(width_factor, height_factor);
    m_size = size;
    m_states[NEED_RESIZE] = false;
}

void Image::resize(float width, float height)
{
    resize(sf::Vector2f(width, height));
}

/**
 * @brief Synchronizes Image sprite with a color modifier
 * and a scaling if needed
 *
 * @author Arthur
 * @date 06/07/2020
 */
void Image::sync()
{
    m_sprite.setColor(m_fillColor);

    if (m_states.at(NEED_RESIZE)) {
        resize(getSize());
    }
}


/**
 * @brief Draws the Image
 *
 * @param target the drawing target
 * @param states the rendering states
 *
 * @author Arthur
 * @date 06/07/2020
 */
void Image::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (isVisible()) {
        target.draw(m_sprite, states);
    }
}

void Image::processTextureLoading(const string& file)
{
    AbstractTexturedMaterial::processTextureLoading(file); //FIXME shows that duplication is here
    m_sprite.setTexture(m_texture);
}

void Image::setOrigin(float x, float y)
{
    m_sprite.setOrigin(x, y);
}

void Image::setPosition(float x, float y)
{
    m_sprite.setPosition(x, y);
}

void Image::setTextureRect(const sf::IntRect&)
{
    //TODO: undefined
}

void Image::resize(float size)
{
    resize(size, size);
}

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin
