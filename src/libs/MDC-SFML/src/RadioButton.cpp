#include "Button.h"
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
 *
 * @param x the x-axis coordinate
 * @param y the y-axis coordinate
 * @param diameter the diameter
 *
 * @author Arthur
 * @date 23/12/16 - 02/01/18
 */
RadioButton::RadioButton(float x, float y, float diameter) :
        Button(x, y, diameter, diameter), m_isSelected{false}
{
    m_labelPosition = RIGHT;
    setRadioClipRect();
    loadAndApplyTextureFromImageFile(Config::RADIO_BUTTON_IMAGE);
    applyColor();
    resize(m_width, m_height);
}


/**
 * Parameterized Constructor with label description
 *
 * @param x the x-axis coordinate
 * @param y the y-axis coordinate
 * @param diameter the diameter
 * @param label the radio label
 * @param customImage a custom image (optional)
 *
 * @author Arthur
 * @date 23/12/16 - 26/09/18
 */
RadioButton::RadioButton(float x, float y, float diameter, const string& label, const string& customImage) :
        Button(x, y, diameter, diameter, label), m_isSelected{false}
{
    m_labelPosition = RIGHT;
    setRadioClipRect();
    loadAndApplyTextureFromImageFile(customImage);
    applyColor();
    resize(m_width, m_height);
}


/**
 * Copy Constructor
 *
 * @param other another button object to copy
 *
 * @author Arthur
 * @date 02/01/17
 */
RadioButton::RadioButton(RadioButton const& other) :
        Button(other), m_isSelected{other.m_isSelected}
{}


/**
 * Destructor
 * @author Arthur
 * @date 23/12/16
 */
RadioButton::~RadioButton() = default;


//------------------------------------------------
//          GETTERS
//------------------------------------------------

bool RadioButton::isSelected() const { return m_isSelected; }


//------------------------------------------------
//          SETTERS
//------------------------------------------------

void RadioButton::setSelected(bool selected) { m_isSelected = selected; }
void RadioButton::setLabelPosition(LabelPosition labelPosition)
{
    switch (labelPosition)
    {
        case LEFT:
            m_labelPosition = LEFT;
            break;
        case RIGHT:
            m_labelPosition = RIGHT;
            break;
        default:
            Config::printError("Not allowed label position");
    }
}


//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Synchronizes Button sprite by applying color modifiers,
 * animating sprite (by changing current texture rect
 * depending on pressed/selected/enabled state) and
 * resizing to diameter the button size after texture applying
 * (because texture overrides size)
 *
 * @author Arthur
 * @date 23/12/16 - 12/09/18
 */
void RadioButton::sync()
{
    applyColor();

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
 * Synchronizes button label position (always left or right)
 * @author Arthur
 * @date 23/12/16 - 27/12/17
 */
void RadioButton::syncLabelPosition()
{
    if (!m_label.getDescription().empty()) {
        switch (m_labelPosition)
        {
            case LEFT:
                m_label.setPosition(getX() - (m_label.getWidth() + getWidth()), getY() - 2);
                m_label.setOrigin(0, 0);
                break;
            case RIGHT:
                m_label.setPosition(getX() + 2 * getWidth(), getY() - 2);
                m_label.setOrigin(0, 0);
                break;
            default:
                Config::printError("Not allowed label position");
        }
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