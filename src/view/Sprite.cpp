#include "Sprite.h"

using namespace std::chrono;

/**
 * Constructs a sprite with a position, a size,
 * an image containing different clips
 * and an array detailing the image clips
 * @author Arthur
 * @date 03/03/16 - 22/05/16
 */
Sprite::Sprite(
        float x, float y, float width, float height, const std::string &image,
        const std::vector<sf::IntRect> &clipRect) :
        GraphicElement(x, y, width, height, image), m_clipRectArray{clipRect},
        m_currentClipRect{0}, m_lastAnimationTime{system_clock::now() }
{
    this->setTextureRect(m_clipRectArray[m_currentClipRect]);
}


/**
 * Copy Constructor
 * @author Arthur
 * @date 19/03/16 - 22/05/16
 */
Sprite::Sprite(const Sprite& other) :
    GraphicElement(other), m_clipRectArray{other.m_clipRectArray},
    m_currentClipRect{0}, m_lastAnimationTime{system_clock::now() }
{
    this->setTextureRect(m_clipRectArray[m_currentClipRect]);
}


/**
 * Destructor
 * @author Arthur
 * @date 05/03/16
 */
Sprite::~Sprite()
{}


//=== Setters

void Sprite::setClipRectArray(std::vector<sf::IntRect> clipRectsArray)
{
    m_clipRectArray = clipRectsArray;
}


/**
 * Changes the current sprite animation image
 * in function of the animation delay
 * @author Arthur
 * @date 03/03/16 - 22/05/16
 */
void Sprite::sync()
{
    system_clock::duration duration = system_clock::now() - m_lastAnimationTime;

    if (duration > milliseconds(ANIMATION_DELAY))
    {
        if (m_currentClipRect == m_clipRectArray.size()-1)
            m_currentClipRect = 0;
        else
            m_currentClipRect++;

        this->setTextureRect(m_clipRectArray[m_currentClipRect]);
        m_lastAnimationTime = system_clock::now();
    }
}
