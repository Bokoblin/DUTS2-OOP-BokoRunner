#include "Button.h"
#include "ToggleButton.h"
#include "ClipRectUtils.h"

using std::string;

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

//------------------------------------------------
//          CONSTRUCTORS / DESTRUCTOR
//------------------------------------------------

/**
 * Constructs a toggle button with provided parameters
 *
 * @param x the x-axis coordinate
 * @param y the y-axis coordinate
 * @param diameter the diameter
 * @param label the toggle label (optional)
 * @param customImage a custom image (optional)
 *
 * @author Arthur
 * @date 28/04/2020 - 02/05/2020
 */
ToggleButton::ToggleButton(float x, float y, float width, float height, const string& label, const string& customImage) :
        Button(x, y, width, height, label), m_isToggled{false}
{
    setOrigin(0, height / 2);
    m_labelPosition = RIGHT;
    setClipRectArray(ClipRectUtils::generate(0, 0, (int) width, (int) height, 4, 2));
    setTextureRect(m_clipRectArray[m_currentClipRect]);

    ToggleButton::loadAndApplyTextureFromImageFile(customImage);
    ToggleButton::applyColor();
    ToggleButton::resize(m_width, m_height);
}


/**
 * Copy Constructor
 *
 * @param other another button object to copy
 *
 * @author Arthur
 * @date 28/04/2020
 */
ToggleButton::ToggleButton(ToggleButton const& other) :
        Button(other), m_isToggled{other.m_isToggled} {}


//------------------------------------------------
//          GETTERS
//------------------------------------------------

bool ToggleButton::isToggled() const { return m_isToggled; }


//------------------------------------------------
//          SETTERS
//------------------------------------------------

void ToggleButton::setToggled(bool toggled) { m_isToggled = toggled; }

void ToggleButton::setLabelPosition(const LabelPosition& labelPosition)
{
    switch (labelPosition) {
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
 * depending on pressed/toggled/enabled state) and
 * resizing the button size after texture applying
 * (because texture overrides size)
 *
 * @author Arthur
 * @date 28/04/2020 - 02/05/2020
 */
void ToggleButton::sync()
{
    applyColor();

    m_currentClipRect = ClipRectUtils::binaryToDecimal(100 * !m_isEnabled + 10 * !m_isToggled + m_isPressed);
    this->setTextureRect(m_clipRectArray[m_currentClipRect]);

    resize(m_width, m_height); //Needed for correct size after reloading texture rectangle clip
    syncLabelPosition();
}

/**
 * Synchronizes button label position (always left or right)
 * @author Arthur
 * @date 28/04/2020 - 02/05/2020
 */
void ToggleButton::syncLabelPosition()
{
    if (!m_label.getDescription().empty()) {
        switch (m_labelPosition) {
            case LEFT:
                m_label.setPosition(getX() - (HORIZONTAL_LABEL_MARGIN + m_label.getWidth()), getY());
                m_label.setOrigin(0, m_label.getHeight());
                break;
            case RIGHT:
                m_label.setPosition(getX() + m_width + HORIZONTAL_LABEL_MARGIN, getY());
                m_label.setOrigin(0, m_label.getHeight());
                break;
            default:
                Config::printError("Not allowed label position");
        }
    }
}

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin