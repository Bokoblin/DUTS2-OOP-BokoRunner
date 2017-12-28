#include "AnimatedSprite.h"

/**
 * Constructs a sprite with a position, a size,
 * an image containing different clips
 * and an array detailing the image clips
 * @author Arthur
 * @date 03/03/16 - 22/05/16
 * @param x the sprite's x position
 * @param y the sprite's y position
 * @param width the sprite's width
 * @param height the sprite's height
 * @param image the file to use for sprite texture
 * @param clipRect the part of the image to use for texture
 */
AnimatedSprite::AnimatedSprite(float x, float y, float width, float height, const std::string &image,
               const std::vector<sf::IntRect> &clipRect) :
        GraphicElement(x, y, width, height, image), m_clipRectArray{clipRect},
        m_currentClipRect{0}, m_lastAnimationTime{std::chrono::system_clock::now() }
{
    this->setTextureRect(m_clipRectArray[m_currentClipRect]);
}


/**
 * Copy Constructor
 * @author Arthur
 * @date 19/03/16 - 22/05/16
 *
 * @param other another sprite object to copy
 */
AnimatedSprite::AnimatedSprite(const AnimatedSprite& other) :
        GraphicElement(other), m_clipRectArray{other.m_clipRectArray},
        m_currentClipRect{0}, m_lastAnimationTime{std::chrono::system_clock::now() }
{
    this->setTextureRect(m_clipRectArray[m_currentClipRect]);
}


/**
 * Destructor
 * @author Arthur
 * @date 05/03/16
 */
AnimatedSprite::~AnimatedSprite() = default;


//=== Setters

void AnimatedSprite::setClipRectArray(std::vector<sf::IntRect> clipRectsArray)
{
    m_clipRectArray = std::move(clipRectsArray);
}


/**
 * Changes the current sprite animation image
 * in function of the animation delay
 * @author Arthur
 * @date 03/03/16 - 22/05/16
 */
void AnimatedSprite::sync()
{
    GraphicElement::sync();

    std::chrono::system_clock::duration duration = std::chrono::system_clock::now() - m_lastAnimationTime;

    if (duration > std::chrono::milliseconds(ANIMATION_DELAY))
    {
        if (m_currentClipRect == m_clipRectArray.size()-1)
            m_currentClipRect = 0;
        else
            m_currentClipRect++;

        this->setTextureRect(m_clipRectArray[m_currentClipRect]);
        m_lastAnimationTime = std::chrono::system_clock::now();
    }
}
