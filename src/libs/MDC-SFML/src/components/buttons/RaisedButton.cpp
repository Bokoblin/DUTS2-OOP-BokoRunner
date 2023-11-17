#include "RaisedButton.h"

using std::string;

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

//------------------------------------------------
//          CONSTRUCTORS / DESTRUCTOR
//------------------------------------------------

/**
 * @brief Constructs a raised button with coordinates,
 * a size, a label and a texture image
 *
 * @param x the x-axis coordinate
 * @param y the y-axis coordinate
 * @param width the width
 * @param height the height
 * @param label the label's description (optional)
 * @param customImage a custom image (optional)
 *
 * @author Arthur
 * @date 12/09/2018 - 28/06/2020
 */
RaisedButton::RaisedButton(float x, float y, float width, float height, const string& label, const string& customImage) :
        Button(x, y, width, height, CENTER, label, customImage),
        m_initialPos{x, y}, m_resetScale{1.0f, 1.0f}
{
}

/**
 * @brief Copy Constructor
 *
 * @param other another button object to copy
 *
 * @author Arthur
 * @date 12/09/2018 - 20/09/2018
 */
RaisedButton::RaisedButton(RaisedButton const& other) :
        Button(other), m_initialPos{other.m_initialPos}, m_resetScale{other.m_resetScale} {}


//------------------------------------------------
//          SETTERS
//------------------------------------------------

/**
 * @brief Changes the button on pressed state change
 * @param pressed
 * @author Arthur
 * @date 12/09/2018 - 28/06/2020
 */
void RaisedButton::setPressed(bool pressed)
{
    if (pressed != m_states.at(PRESSED)) {
        if (pressed) {
            m_buttonSprite.setScale(0.95f * m_buttonSprite.getScale().x, 0.95f * m_buttonSprite.getScale().y);
            m_buttonSprite.setPosition(getX() + 0.025f * getSize().x, getY() + 0.025f * getSize().y);
        } else {
            m_buttonSprite.setScale(m_resetScale.x, m_resetScale.y);
            m_buttonSprite.setPosition(m_initialPos.x, m_initialPos.y);
        }
    }
    m_states[PRESSED] = pressed;
}


//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * @brief Synchronizes button sprite
 *
 * @author Arthur
 * @date 06/04/2016 - 20/09/2018
 */
void RaisedButton::sync()
{
    m_buttonSprite.setColor(m_fillColor);
}


/**
 * @brief Sync the raised button's label position and wrap the text if it is too long
 *
 * @author Arthur
 * @date 12/09/2018 - 30/10/2018
 */
void RaisedButton::syncLabelPosition()
{
    Button::syncLabelPosition();

    //Adapt text size to button (with a margin considered)
    while (m_label.getSize().x > (getSize().x - 0.1f * getSize().x)
            || m_label.getSize().y > (getSize().y - 0.1f * getSize().y)) {
        m_label.setCharacterSize(m_label.getCharacterSize() - 1);
        m_label.setPositionSelfCentered(getX() + 0.5f * getSize().x, getY() + 0.5f * getSize().y);
    }
}

/**
 * @brief Enable resize only when not pressed
 *
 * @param size a size to apply
 *
 * @author Arthur
 * @date 12/09/2018 - 05/07/2020
 */
void RaisedButton::resize(const sf::Vector2f& size) { resize(size.x, size.y); }

/**
 * @brief Enable resize only when not pressed
 *
 * @param width the new width
 * @param height the new height
 *
 * @author Arthur
 * @date 12/09/2018 - 05/07/2020
 */
void RaisedButton::resize(float width, float height)
{
    if (!m_states.at(PRESSED)) {
        m_resetScale = sf::Vector2f(width / getWidth(), height / getHeight());
        Button::resize(width, height);
    }
}

void RaisedButton::resize(float size)
{
    resize(size, size);
}

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin
