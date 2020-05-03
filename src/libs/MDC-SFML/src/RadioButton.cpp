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
 * Constructs a toggle button with provided parameters
 *
 * @param x the x-axis coordinate
 * @param y the y-axis coordinate
 * @param origDiameter the original image diameter
 * @param newDiameter the new diameter
 * @param label the radio label
 * @param customImage a custom image (optional)
 * @param labelPosition the label position (optional)
 * @param isSelected the default state (optional)
 *
 * @author Arthur
 * @date 23/12/2016 - 03/05/2020
 */
RadioButton::RadioButton(float x, float y, float origDiameter, float newDiameter, const string& label,
                         const string& customImage, LabelPosition labelPosition, bool isSelected) :
        AbstractStateButton(x, y, origDiameter, origDiameter, newDiameter, newDiameter,
                            label, customImage, labelPosition, isSelected) {}

/**
 * Copy Constructor
 *
 * @param other another button object to copy
 *
 * @author Arthur
 * @date 02/01/2017 - 03/05/2020
 */
RadioButton::RadioButton(RadioButton const& other) :
        AbstractStateButton(other) {}

//------------------------------------------------
//          GETTERS
//------------------------------------------------

bool RadioButton::isSelected() const { return m_isChecked; }

//------------------------------------------------
//          SETTERS
//------------------------------------------------

void RadioButton::setSelected(bool selected) { m_isChecked = selected; }

//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Synchronizes button label position (always left or right)
 *
 * @author Arthur
 * @date 23/12/2016 - 03/05/2020
 */
void RadioButton::syncLabelPosition()
{
    if (!m_label.getDescription().empty()) {
        switch (m_labelPosition) {
            case LEFT:
                m_label.setPosition(getX() - (HORIZONTAL_LABEL_MARGIN + m_label.getWidth()), getY() + getHeight() / 2 - 3);
                m_label.setOrigin(0, m_label.getHeight() / 2);
                break;
            case RIGHT:
                m_label.setPosition(getX() + m_width + HORIZONTAL_LABEL_MARGIN, getY() + getHeight() / 2 - 3);
                m_label.setOrigin(0, m_label.getHeight() / 2);
                break;
            default:
                Config::printError("Not allowed label position");
        }
    }
}

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin