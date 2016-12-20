#include "AnimatedGraphicElement.h"

using namespace std::chrono;

/**
 * Parameterized Constructor
 * @author Arthur
 * @date 3/03 - 22/05
 */
AnimatedGraphicElement::AnimatedGraphicElement(sf::Texture &image, float x,
        float y, float w, float h, const std::vector<sf::IntRect> & clipRect):
    GraphicElement(image, x, y, w, h), m_clipRectArray{clipRect},
    m_currentClipRect{0}, m_lastAnimationTime{system_clock::now() }
{
    this->setTextureRect(m_clipRectArray[m_currentClipRect]);
}


/**
 * Copy Constructor
 * @author Arthur
 * @date 19/03 - 22/05
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
 * @date 5/03
 */
AnimatedGraphicElement::~AnimatedGraphicElement()
{}


//=== Setters

void AnimatedGraphicElement::setClipRectArray(std::vector<sf::IntRect> crA)
{
    m_clipRectArray = crA;
}


/**
 * Synchronization Function : change animation
 * @author Arthur
 * @date 3/03 - 22/05
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
