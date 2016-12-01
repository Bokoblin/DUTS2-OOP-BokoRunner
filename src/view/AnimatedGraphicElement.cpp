#include "AnimatedGraphicElement.h"

using namespace std::chrono;

/********************************************
    Parameterized Constructor
*********************************************
    @author Arthur  @date 3/03 - 22/05
*********************************************/
AnimatedGraphicElement::AnimatedGraphicElement(sf::Texture &image, float x,
        float y, float w, float h, const std::vector<sf::IntRect> & clipRects):
    GraphicElement(image, x, y, w, h), m_clipRectsArray{clipRects},
    m_currentClipRect{0}, m_lastAnimationTime{system_clock::now() }
{
    this->setTextureRect(m_clipRectsArray[m_currentClipRect]);
}


/********************************************
    Copy Constructor
*********************************************
    @author Arthur  @date 19/03 - 22/05
*********************************************/
AnimatedGraphicElement::AnimatedGraphicElement(const AnimatedGraphicElement& other) :
    GraphicElement(other), m_clipRectsArray{other.m_clipRectsArray},
    m_currentClipRect{0}, m_lastAnimationTime{system_clock::now() }
{
    this->setTextureRect(m_clipRectsArray[m_currentClipRect]);
}


/********************************************
    Destructor
*********************************************
    @author Arthur  @date 5/03
*********************************************/
AnimatedGraphicElement::~AnimatedGraphicElement()
{}

/********************************************
    Setter
*********************************************
    @author Arthur  @date 20/05
*********************************************/
void AnimatedGraphicElement::setClipRectArray(std::vector<sf::IntRect> crA)
{
    m_clipRectsArray = crA;
}


/********************************************
    Synchronization Function : change animation
*********************************************
    @author Arthur  @date 3/03 - 22/05
*********************************************/
void AnimatedGraphicElement::sync()
{
    system_clock::duration duration = system_clock::now() - m_lastAnimationTime;

    if ( duration > milliseconds(ANIM_DELAY) )
    {
        if (m_currentClipRect == m_clipRectsArray.size()-1 )
            m_currentClipRect = 0;
        else
            m_currentClipRect++;

        this->setTextureRect(m_clipRectsArray[m_currentClipRect]);
        m_lastAnimationTime = system_clock::now();
    }
}
