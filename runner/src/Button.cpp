#include "../header/Button.h"

/********************************************
    Parameterized Constructor
*********************************************
    @author Arthur  @date 6/04 - 20/05
*********************************************/
Button::Button(const std::vector<sf::IntRect> & clipRects,
            sf::Texture &image, float x, float y, float w, float h, bool isRadio):
            GraphicElement(image, x, y, w, h), m_clipRectsArray{clipRects},
            m_currentClipRect{0}, m_isRadio{isRadio},  m_pressed{false},
            m_active{false}, m_disabled{false}
{
    this->setTextureRect(m_clipRectsArray[m_currentClipRect]);
}


/********************************************
    Copy Constructor
*********************************************
    @author Arthur  @date 6/04 - 14/04
*********************************************/
Button::Button(Button const& other) :
    GraphicElement(other), m_clipRectsArray{other.m_clipRectsArray},
    m_currentClipRect{0}, m_isRadio{other.m_isRadio}, m_pressed{false}, m_active{false}
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
    Getters
*********************************************
    @author Arthur  @date 20/05
*********************************************/
bool Button::getDisabledState() const { return m_disabled; }


/********************************************
    Setters
*********************************************
    @author Arthur  @date 6/04 - 20/05
*********************************************/
void Button::setPressedState(bool state) { m_pressed = state; }
void Button::setActivatedState(bool state) { m_active = state; }
void Button::setDisabledState(bool state) { m_disabled = state; }


/********************************************
    Synchronization Function : change animation
*********************************************
    @author Arthur  @date 6/04 - 20/05
*********************************************/
void Button::sync()
{
    if ( m_isRadio == false)
        this->setTextureRect(m_clipRectsArray[m_pressed]);
    else
    {
        if ( !m_disabled && m_active && !m_pressed )
            this->setTextureRect(m_clipRectsArray[0]);
        if ( !m_disabled && m_active && m_pressed )
            this->setTextureRect(m_clipRectsArray[1]);
        if ( !m_disabled && !m_active && !m_pressed )
            this->setTextureRect(m_clipRectsArray[2]);
        if ( !m_disabled && !m_active && m_pressed )
            this->setTextureRect(m_clipRectsArray[3]);
        if ( m_disabled && m_active)
            this->setTextureRect(m_clipRectsArray[4]);
        if ( m_disabled && !m_active)
            this->setTextureRect(m_clipRectsArray[5]);
    }
}
