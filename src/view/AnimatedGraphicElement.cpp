#include "AnimatedGraphicElement.h"

#include <utility>

using namespace std::chrono;

/**
 * Parameterized Constructor
 * @author Arthur
 * @date 03/03/16 - 10/04/17
 */
AnimatedGraphicElement::AnimatedGraphicElement(
        float x, float y, float w, float h,
        const std::string &image, const std::vector<sf::IntRect> &clipRect) :
    GraphicElement(x, y, w, h, image), m_clipRectArray{clipRect},
    m_currentClipRect{0}, m_lastAnimationTime{system_clock::now() }
{
    this->setTextureRect(m_clipRectArray[m_currentClipRect]);
}


/**
 * Copy Constructor
 * @author Arthur
 * @date 19/03/16 - 22/05/16
 */
AnimatedGraphicElement::AnimatedGraphicElement(const AnimatedGraphicElement& other) :
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
AnimatedGraphicElement::~AnimatedGraphicElement() = default;


//=== Setters

void AnimatedGraphicElement::setClipRectArray(std::vector<sf::IntRect> clipRectsArray)
{
    m_clipRectArray = std::move(clipRectsArray);
}


/**
 * Synchronization Function : change animation
 * @author Arthur
 * @date 03/03/16 - 22/05/16
 */
void AnimatedGraphicElement::sync()
{
    system_clock::duration duration = system_clock::now() - m_lastAnimationTime;

    if ( duration > milliseconds(ANIM_DELAY) )
    {
        if (m_currentClipRect == m_clipRectArray.size()-1 )
            m_currentClipRect = 0;
        else
            m_currentClipRect++;

        this->setTextureRect(m_clipRectArray[m_currentClipRect]);
        m_lastAnimationTime = system_clock::now();
    }
}
