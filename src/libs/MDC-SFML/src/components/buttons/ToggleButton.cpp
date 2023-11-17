#include "ToggleButton.h"

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
 * @param labelPosition the label position (optional)
 * @param isToggled the default state (optional)
 *
 * @author Arthur
 * @date 28/04/2020 - 03/05/2020
 */
ToggleButton::ToggleButton(float x, float y, float width, float height, const string& label,
                           const string& customImage, LabelPosition labelPosition, bool isToggled) :
        AbstractStateButton(x, y, width, height, width, height, label, customImage, labelPosition, isToggled)
{
    m_buttonSprite.setOrigin(0, height / 2);
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
        AbstractStateButton(other) {}

//------------------------------------------------
//          GETTERS
//------------------------------------------------

bool ToggleButton::isToggled() const { return m_states.at(CHECKED); }

//------------------------------------------------
//          SETTERS
//------------------------------------------------

void ToggleButton::setToggled(bool toggled) { m_states[CHECKED] = toggled; }

//------------------------------------------------
//          METHODS
//------------------------------------------------

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
                m_label.setPosition(getX() + getSize().x + HORIZONTAL_LABEL_MARGIN, getY());
                m_label.setOrigin(0, m_label.getHeight());
                break;
            default:
                Config::printError("Not allowed label position");
        }
    }
}

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin