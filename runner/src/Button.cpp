#include "../header/Button.h"

/********************************************
    Parameterized Constructor
*********************************************
    @author Arthur  @date 6/04
*********************************************/
Button::Button(const std::vector<sf::IntRect> & clipRects,
            sf::Texture &image, float x, float y, float w, float h):
    GraphicElement(image, x, y, w, h), m_clipRectsArray{clipRects},
    m_currentClipRect{0}, m_pressedState{false}
{
    this->setTextureRect(m_clipRectsArray[m_currentClipRect]);
}


/********************************************
    Copy Constructor
*********************************************
    @author Arthur  @date 6/04
*********************************************/
Button::Button(Button const& elementACopier) :
    GraphicElement(elementACopier), m_clipRectsArray{elementACopier.m_clipRectsArray},
    m_currentClipRect{0}, m_pressedState{false}
{
    this->setTextureRect(m_clipRectsArray[m_currentClipRect]);
}


/********************************************
    Destructor
*********************************************
    @author Arthur  @date 6/04
*********************************************/
Button::~Button()
{}


/********************************************
    Setters
*********************************************
    @author Arthur  @date 6/04
*********************************************/
void Button::setPressedState(bool state) { m_pressedState = state; }


/********************************************
    Synchronization Function : change animation
*********************************************
    @author Arthur  @date 6/04 - 11/04
*********************************************/
void Button::sync()
{
    this->setTextureRect(m_clipRectsArray[m_pressedState]);
}
