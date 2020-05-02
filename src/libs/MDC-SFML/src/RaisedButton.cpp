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
 * @brief Constructs a raised button with coordinates and a size
 *
 * @param x the x-axis coordinate
 * @param y the y-axis coordinate
 * @param width the width
 * @param height the height
 *
 * @author Arthur
 * @date 12/09/18 - 20/09/18
 */
RaisedButton::RaisedButton(float x, float y, float width, float height) :
        Button(x, y, width, height), m_initialPos{x, y}, m_initialScale{1.0f, 1.0f}
{
    m_font.loadFromFile(Config::DEFAULT_CONDENSED_FONT);
    m_label.setFont(m_font);
    m_label.setFillColor(sf::Color::White);
    m_label.setCharacterSize(DEFAULT_CHAR_SIZE);
    m_label.setDescription("");
    RaisedButton::syncLabelPosition();
}


/**
 * @brief Constructs a button with coordinates,
 * a size, a label and a texture image
 *
 * @param x the x-axis coordinate
 * @param y the y-axis coordinate
 * @param width the width
 * @param height the height
 * @param label the label's description
 * @param customImage a custom image (optional)
 *
 * @author Arthur
 * @date 12/09/18 - 12/10/18
 */
RaisedButton::RaisedButton(float x, float y, float width, float height, const string& label, const string& customImage) :
        RaisedButton(x, y, width, height)
{
    m_label.setDescription(label);
    RaisedButton::syncLabelPosition();
    RaisedButton::loadAndApplyTextureFromImageFile(customImage);
    RaisedButton::applyColor();
}


/**
 * @brief Copy Constructor
 *
 * @param other another button object to copy
 *
 * @author Arthur
 * @date 12/09/18 - 20/09/18
 */
RaisedButton::RaisedButton(RaisedButton const& other) :
        Button(other), m_initialPos{other.m_initialPos}, m_initialScale{other.m_initialScale}
{
    this->setTextureRect(m_clipRectArray[m_currentClipRect]);
}


/**
 * @brief Destructor
 * @author Arthur
 * @date 12/09/18
 */
RaisedButton::~RaisedButton() = default;


//------------------------------------------------
//          SETTERS
//------------------------------------------------

/**
 * @brief Changes the button on pressed state change
 * @param pressed
 * @author Arthur
 * @date 12/09/18 - 20/09/18
 */
void RaisedButton::setPressed(bool pressed)
{
    if (pressed != m_isPressed) {
        if (pressed) {
            this->setScale(0.95f * getScale().x, 0.95f * getScale().y);
            this->setPosition(getX() + 0.025f * m_width, getY() + 0.025f * m_height);
        } else {
            this->setScale(m_initialScale.x, m_initialScale.y);
            this->setPosition(m_initialPos.x, m_initialPos.y);
        }
    }
    m_isPressed = pressed;
}


//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * @brief Synchronizes button sprite
 *
 * @author Arthur
 * @date 06/04/16 - 20/09/18
 */
void RaisedButton::sync()
{
    applyColor();
}


/**
 * @brief Sync the raised button's label position and wrap the text if it is too long
 *
 * @author Arthur
 * @date 12/09/18 - 30/10/18
 */
void RaisedButton::syncLabelPosition()
{
    Button::syncLabelPosition();

    //Adapt text size to button (with a margin considered)
    while (m_label.getWidth() > (getWidth() - 0.1f * getWidth())
            || m_label.getHeight() > (getHeight() - 0.1f * getHeight())) {
        m_label.setCharacterSize(m_label.getCharacterSize() - 1);
        m_label.setPositionSelfCentered(getX() + 0.5f * getWidth(), getY() + 0.5f * getHeight());
    }
}


/**
 * @brief Enable resize only when not pressed
 *
 * @param width the new width
 * @param height the new height
 *
 * @author Arthur
 * @date 12/09/18 - 20/09/18
 */
void RaisedButton::resize(float width, float height)
{
    if (!m_isPressed) {
        m_initialScale = sf::Vector2f(width / getWidth(), height / getHeight());
        Sprite::resize(width, height);
    }
}

/**
 * @brief Enable resize only when not pressed
 *
 * @param size the new size
 *
 * @author Arthur
 * @date 12/09/18
 */
void RaisedButton::resize(float size)
{
    resize(size, size);
}

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin
