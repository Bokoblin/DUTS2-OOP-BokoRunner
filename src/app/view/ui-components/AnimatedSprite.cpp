#include "AnimatedSprite.h"

//------------------------------------------------
//          CONSTRUCTORS / DESTRUCTOR
//------------------------------------------------

/**
 * Constructs a sprite with a size,
 * an image containing different clips
 * and an array detailing the image clips
 *
 * @param width the sprite's width
 * @param height the sprite's height
 * @param image the file to use for sprite texture
 * @param clipRect the part of the image to use for texture
 *
 * @author Arthur
 * @date 03/05/2020 - 02/07/2020
 */
AnimatedSprite::AnimatedSprite(float width, float height, const std::string& image,
                               const std::vector<sf::IntRect>& clipRect) :
        mdsf::Image(width, height, image), m_clipRectArray{clipRect},
        m_currentClipRect{0}, m_lastAnimationTime{std::chrono::system_clock::now()}
{
    m_sprite.setTextureRect(m_clipRectArray[m_currentClipRect]);
}

/**
 * Constructs a sprite with a position, a size,
 * an image containing different clips
 * and an array detailing the image clips
 *
 * @param x the sprite's x position
 * @param y the sprite's y position
 * @param width the sprite's width
 * @param height the sprite's height
 * @param image the file to use for sprite texture
 * @param clipRect the part of the image to use for texture
 *
 * @author Arthur
 * @date 03/03/2016 - 02/07/2020
 */
AnimatedSprite::AnimatedSprite(float x, float y, float width, float height, const std::string& image,
                               const std::vector<sf::IntRect>& clipRect) :
        mdsf::Image(x, y, width, height, image), m_clipRectArray{clipRect},
        m_currentClipRect{0}, m_lastAnimationTime{std::chrono::system_clock::now()}
{
    m_sprite.setTextureRect(m_clipRectArray[m_currentClipRect]);
}


/**
 * Copy Constructor
 *
 * @param other another sprite object to copy
 *
 * @author Arthur
 * @date 19/03/2016 - 02/07/2020
 */
AnimatedSprite::AnimatedSprite(const AnimatedSprite& other) :
        mdsf::Image(other), m_clipRectArray{other.m_clipRectArray},
        m_currentClipRect{0}, m_lastAnimationTime{std::chrono::system_clock::now()}
{
    m_sprite.setTextureRect(m_clipRectArray[m_currentClipRect]);
}


/**
 * Destructor
 * @author Arthur
 * @date 05/03/16
 */
AnimatedSprite::~AnimatedSprite() = default;


//------------------------------------------------
//          SETTERS
//------------------------------------------------

void AnimatedSprite::setClipRectArray(std::vector<sf::IntRect> clipRectsArray)
{
    m_clipRectArray = std::move(clipRectsArray);
}


//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Changes the current sprite animation image
 * in function of the animation delay
 * @author Arthur
 * @date 03/03/16 - 22/05/16
 */
void AnimatedSprite::sync()
{
    m_sprite.setColor(m_fillColor);

    std::chrono::system_clock::duration duration = std::chrono::system_clock::now() - m_lastAnimationTime;

    if (duration > std::chrono::milliseconds(ANIMATION_DELAY)) {
        if (m_currentClipRect == m_clipRectArray.size() - 1) {
            m_currentClipRect = 0;
        } else {
            m_currentClipRect++;
        }

        m_sprite.setTextureRect(m_clipRectArray[m_currentClipRect]);
        m_lastAnimationTime = std::chrono::system_clock::now();
    }
}
