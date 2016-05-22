#include "../header/AnimatedGraphicElement.h"

using namespace std::chrono;

/********************************************
    Parameterized Constructor
*********************************************
    @author Arthur  @date 3/03 - 6/04
*********************************************/
AnimatedGraphicElement::AnimatedGraphicElement(sf::Texture &image, float x, float y, float w,
            float h, const std::vector<sf::IntRect> & clipRects, unsigned int separator):
    GraphicElement(image, x, y, w, h), m_clipRectsArray{clipRects},
    m_currentClipRect{0}, m_lastAnimationTime{system_clock::now() }, m_arraySeparator{separator}
{
    this->setTextureRect(m_clipRectsArray[m_currentClipRect]);
}


/********************************************
    Copy Constructor
*********************************************
    @author Arthur  @date 19/03 - 6/04
*********************************************/
AnimatedGraphicElement::AnimatedGraphicElement(AnimatedGraphicElement const& other) :
    GraphicElement(other), m_clipRectsArray{other.m_clipRectsArray},
    m_currentClipRect{0}, m_lastAnimationTime{system_clock::now() }, m_arraySeparator{other.m_arraySeparator}
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
    @author Arthur  @date 3/03 - 6/04
*********************************************/
void AnimatedGraphicElement::sync()
{
    system_clock::duration duration = system_clock::now() - m_lastAnimationTime;

    if ( duration > milliseconds(200) )
    {
        if (m_currentClipRect == m_arraySeparator-1)
            m_currentClipRect = 0;
        else
            m_currentClipRect++;

        this->setTextureRect(m_clipRectsArray[m_currentClipRect]);
        m_lastAnimationTime = system_clock::now();
    }
}
