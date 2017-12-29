#include "RadioButton.h"

using std::string;

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

//------------------------------------------------
//          CONSTRUCTORS / DESTRUCTOR
//------------------------------------------------

/**
 * Parameterized Constructor without label description
 * @author Arthur
 * @date 23/12/16 - 02/01/17
 */
RadioButton::RadioButton(float x, float y, float w, float h) :
        Button(x, y, w, h)
{
    setRadioClipRect();
    setTextureFromImage(RADIO_BUTTONS_IMAGE);
}


/**
 * Parameterized Constructor with label description
 * @author Arthur
 * @date 23/12/16 - 02/01/17
 */
RadioButton::RadioButton(float x, float y, float width, float height, const string &label) :
        Button(x, y, width, height, label)
{
    setRadioClipRect();

    if (label != "indicator")
        setTextureFromImage(RADIO_BUTTONS_IMAGE);
    else
        setTextureFromImage(INDICATOR_IMAGE);
}


/**
 * Copy Constructor
 * @author Arthur
 * @date 02/01/17
 */
RadioButton::RadioButton(RadioButton const& other) = default;


/**
 * Destructor
 * @author Arthur
 * @date 23/12/16
 */
RadioButton::~RadioButton() = default;


//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Synchronization Function : change animation
 * @author Arthur
 * @date 23/12/16
 */
void RadioButton::sync()
{
    if (m_isEnabled && m_isSelected && !m_isPressed)
        this->setTextureRect(m_clipRectArray[0]);
    if (m_isEnabled && m_isSelected && m_isPressed)
        this->setTextureRect(m_clipRectArray[1]);
    if (m_isEnabled && !m_isSelected && !m_isPressed)
        this->setTextureRect(m_clipRectArray[2]);
    if (m_isEnabled && !m_isSelected && m_isPressed)
        this->setTextureRect(m_clipRectArray[3]);
    if (!m_isEnabled && m_isSelected)
        this->setTextureRect(m_clipRectArray[4]);
    if (!m_isEnabled && !m_isSelected)
        this->setTextureRect(m_clipRectArray[5]);
}

/**
 * Synchronization Function :
 * Changes animation depending on pressed state
 * sync button's label
 * @author Arthur
 * @date 23/12/16 - 27/12/17
 */
void RadioButton::syncLabelPosition()
{
    if (!m_label.getDescription().empty()) {
        m_label.setPosition(getPosition().x + 2 * getGlobalBounds().width, getPosition().y - 3);
        m_label.setOrigin(0, 0);
    }
}


/**
 * Sets default rectangle clips for radios
 * @author Arthur
 * @date 02/01/17
 */
void RadioButton::setRadioClipRect()
{
    std::vector<sf::IntRect> clipRect;
    clipRect.emplace_back(0, 0, 50, 50);
    clipRect.emplace_back(50, 0, 50, 50);
    clipRect.emplace_back(0, 50, 50, 50);
    clipRect.emplace_back(50, 50, 50, 50);
    clipRect.emplace_back(0, 100, 50, 50);
    clipRect.emplace_back(0, 150, 50, 50);

    setClipRectArray(clipRect);
    setTextureRect(m_clipRectArray[m_currentClipRect]);
}

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin