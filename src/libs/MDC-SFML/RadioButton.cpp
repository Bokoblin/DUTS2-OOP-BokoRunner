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
 * @date 23/12/16 - 02/01/18
 */
RadioButton::RadioButton(float x, float y, float diameter) :
        Button(x, y, diameter, diameter)
{
    setRadioClipRect();
    setTextureFromImage(RADIO_BUTTONS_IMAGE);
    resize(m_width, m_height);
}


/**
 * Parameterized Constructor with label description
 * @author Arthur
 * @date 23/12/16 - 02/01/18
 */
RadioButton::RadioButton(float x, float y, float diameter, const std::string &label) :
        Button(x, y, diameter, diameter, label)
{
    setRadioClipRect();
    setTextureFromImage(label == "indicator" ? INDICATOR_IMAGE : RADIO_BUTTONS_IMAGE);
    resize(m_width, m_height);
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
 * @date 23/12/16 - 02/01/18
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

    resize(m_width, m_height); //Needed for correct size after reloading texture rectangle clip
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