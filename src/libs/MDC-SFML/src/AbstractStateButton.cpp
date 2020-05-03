#include "AbstractStateButton.h"
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
AbstractStateButton::AbstractStateButton(float x, float y, float oldWidth, float oldHeight,
                                         float newWidth, float newHeight, const string& label,
                                         const string& customImage, LabelPosition labelPosition, bool isChecked) :
        Button(x, y, oldWidth, oldHeight, label), m_currentClipRect{0}, m_isChecked{isChecked}
{
    m_labelPosition = labelPosition;

    m_clipRectArray = ClipRectUtils::generate(0, 0, (int) oldWidth, (int) oldHeight, 4, 2);
    setTextureRect(m_clipRectArray[m_currentClipRect]);

    AbstractStateButton::loadAndApplyTextureFromImageFile(customImage);
    AbstractStateButton::applyColor();
    AbstractStateButton::resize(newWidth, newHeight);
}

/**
 * Copy Constructor
 *
 * @param other another button object to copy
 *
 * @author Arthur
 * @date 02/01/2017
 */
AbstractStateButton::AbstractStateButton(AbstractStateButton const& other) :
        Button(other), m_clipRectArray{other.m_clipRectArray}, m_currentClipRect{other.m_currentClipRect},
        m_isChecked{other.m_isChecked}
{
    this->setTextureRect(m_clipRectArray[m_currentClipRect]);
}

//------------------------------------------------
//          SETTERS
//------------------------------------------------

void AbstractStateButton::setLabelPosition(const LabelPosition& labelPosition)
{
    switch (labelPosition) {
        case LEFT:
        case RIGHT:
            m_labelPosition = labelPosition;
            break;
        default:
            Config::printError("Not allowed label position");
    }
}

//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Synchronizes sprite by applying color modifiers, resizing
 * and state visuals (pressed/checked/enabled)
 *
 * @author Arthur
 * @date 23/12/2016 - 03/05/2020
 */
void AbstractStateButton::sync()
{
    applyColor();

    m_currentClipRect = ClipRectUtils::binaryToDecimal(100 * !m_isEnabled + 10 * !m_isChecked + m_isPressed);
    this->setTextureRect(m_clipRectArray[m_currentClipRect]);

    resize(m_width, m_height); //Needed for correct size after reloading texture rectangle clip
    syncLabelPosition();
}

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin