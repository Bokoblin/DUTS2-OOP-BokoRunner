#include "Button.h"

using std::string;

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

//------------------------------------------------
//          CONSTRUCTORS / DESTRUCTOR
//------------------------------------------------

/**
 * Constructs a button with coordinates and a size
 *
 * @param x the x-axis coordinate
 * @param y the y-axis coordinate
 * @param width the width
 * @param height the height
 *
 * @author Arthur
 * @date 02/01/17 - 01/01/18
 */
Button::Button(float x, float y, float width, float height) :
        Sprite(x, y, width, height), m_currentClipRect{0}, m_labelPosition{CENTER},
        m_isPressed{false}, m_isEnabled{true}, m_label{""}
{
    m_font.loadFromFile(Config::DEFAULT_CONDENSED_FONT);
    m_label.setFont(m_font);
    m_label.setFillColor(sf::Color::White);
    m_label.setCharacterSize(22);
}


/**
 * Constructs a button with coordinates,
 * a size and a label description
 *
 * @param x the x-axis coordinate
 * @param y the y-axis coordinate
 * @param width the width
 * @param height the height
 * @param description the label's description
 *
 * @author Arthur
 * @date 02/01/17 - 01/01/18
 */
Button::Button(float x, float y, float width, float height, const string &description) :
        Button(x, y, width, height)
{
    m_label.setDescription(description);
    syncLabelPosition();
}


/**
 * Constructs a button with coordinates,
 * a size, a texture and an image rectangle clip
 *
 * @param x the x-axis coordinate
 * @param y the y-axis coordinate
 * @param width the width
 * @param height the height
 * @param textureImage the button texture image
 * @param clipRect the image part used
 *
 * @author Arthur
 * @date 06/04/16 - 04/01/18
 */
Button::Button(float x, float y, float width, float height,
               const string &textureImage, const std::vector<sf::IntRect> &clipRect) :
        Sprite(x, y, width, height, textureImage), m_clipRectArray{clipRect}, m_currentClipRect{0},
        m_isPressed{false}, m_isEnabled{true}, m_labelPosition{CENTER}, m_label{""}
{
    this->setTextureRect(m_clipRectArray[m_currentClipRect]);

    m_font.loadFromFile(Config::DEFAULT_CONDENSED_FONT);
    m_label.setFont(m_font);
    m_label.setFillColor(sf::Color::White);
    m_label.setCharacterSize(22);
}


/**
 * Constructs a button with coordinates,
 * a size, a label, a texture image and an image rectangle clip
 *
 * @param x the x-axis coordinate
 * @param y the y-axis coordinate
 * @param width the width
 * @param height the height
 * @param description the label's description
 * @param textureImage the button texture image
 * @param clipRect the image part used
 *
 * @author Arthur
 * @date 06/04/16 - 01/01/18
 */
Button::Button(float x, float y, float width, float height, const string &description,
               const string &textureImage, const std::vector<sf::IntRect> &clipRect) :
        Button(x, y, width, height, textureImage, clipRect)
{
    m_label.setDescription(description);
    syncLabelPosition();
}


/**
 * Copy Constructor
 *
 * @param other another button object to copy
 *
 * @author Arthur
 * @date 06/04/16 - 04/01/18
 */
Button::Button(Button const& other) :
        Sprite(other), m_clipRectArray{other.m_clipRectArray}, m_currentClipRect{other.m_currentClipRect},
        m_isPressed{other.m_isPressed}, m_isEnabled{other.m_isEnabled},
        m_font{other.m_font}, m_label{other.m_label}, m_labelPosition{other.m_labelPosition}
{
    this->setTextureRect(m_clipRectArray[m_currentClipRect]);
}


/**
 * Destructor
 * @author Arthur
 * @date 06/04/16 - 25/01/17
 */
Button::~Button() = default;


//------------------------------------------------
//          GETTERS
//------------------------------------------------

bool Button::isPressed() const { return m_isPressed; }
bool Button::isEnabled() const { return m_isEnabled; }
LabelPosition Button::getLabelPosition() const { return m_labelPosition; }


//------------------------------------------------
//          SETTERS
//------------------------------------------------

void Button::setPressed(bool pressed) { m_isPressed = pressed; }
void Button::setEnabled(bool enabled) { m_isEnabled = enabled; }
void Button::setClipRectArray(std::vector<sf::IntRect> array) { m_clipRectArray = std::move(array); }
void Button::setPositionSelfCentered(float x, float y) { setPosition(x-m_width/2, y); }
void Button::setLabelPosition(LabelPosition labelPosition) { m_labelPosition = labelPosition; }
void Button::setLabelDescription(const std::string &description) { m_label.setDescription(description); }


//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Synchronizes Button sprite by animating sprite
 * (by changing current texture rect depending on pressed state)
 *
 * @author Arthur
 * @date 06/04/16 - 04/01/18
 */
void Button::sync()
{
    if (m_isEnabled)
        this->setTextureRect(m_clipRectArray[m_isPressed]); //TODO: Raised buttons: resize instead later (if no Z-axis)
    else
        this->setTextureRect(m_clipRectArray[0]);
}


/**
 * Retrieves the button's label text
 *
 * @param dataBase the app's database //TODO: not for a lib
 *
 * @author Arthur
 * @date 23/12/16 - 27/12/17
 */
void Button::retrieveLabel(const DataBase &dataBase)
{
    if (!m_label.getDescription().empty())
    {
        string utf8_string = dataBase.loadTextFromIdentifier(m_label.getDescription());
        m_label.setString(sf::String::fromUtf8(utf8_string.begin(), utf8_string.end()));
    }
}


/**
 * Sync the button's label position
 * TODO:Raised button: adjust width to text
 *
 * @author Arthur
 * @date 23/12/16 - 04/01/18
 */
void Button::syncLabelPosition()
{
    if (!m_label.getDescription().empty())
    {
        switch (m_labelPosition)
        {
            case TOP:
                m_label.setPositionSelfCentered(getX() + getWidth()/2, getY() - getHeight()/2);
                m_label.setOrigin(0, m_label.getHeight()/2);
                break;
            case RIGHT:
                m_label.setPosition(getX() + getWidth() + 30, getY() + getHeight()/2 - 7);
                m_label.setOrigin(0, m_label.getHeight()/2);
                break;
            case BOTTOM:
                m_label.setPositionSelfCentered(getX() + getWidth()/2, getY() + getHeight() + 50);
                m_label.setOrigin(0, m_label.getHeight()/2);
                break;
            case LEFT:
                m_label.setPosition((getX() - 30), getY() + getHeight()/2 - 7);
                m_label.setOrigin(m_label.getWidth(), m_label.getHeight()/2);
                break;
            case CENTER:
                m_label.setPositionSelfCentered(getX() + getWidth()/2, getY() + getHeight()/2+1);
                m_label.setOrigin(0, m_label.getHeight()/2);
                break;
        }
    }
}


/**
 * Retrieves and syncs the button's label
 * (updates position + displayed text)
 * Note: This function is only a combination of syncLabel() and retrieveLabel()
 *
 * @param dataBase the app's database
 *
 * @author Arthur
 * @date 27/12/17
 */
void Button::retrieveAndSyncLabel(const DataBase &dataBase)
{
    retrieveLabel(dataBase);
    syncLabelPosition();
}


/**
 * Draws the button and its label if visible
 *
 * @param window the app's window
 *
 * @author Arthur
 * @date 23/12/16 - 02/01/18
 */
void Button::draw(sf::RenderWindow *window) const
{
    if (isVisible())
    {
        window->draw(*this);
        m_label.draw(window);
    }
}


/**
 * Checks if a point of given coordinates is contained
 * in the button or its label
 *
 * @param x the x-axis coordinate
 * @param y the y-axis coordinate
 *
 * @author Arthur
 * @date 23/12/16 - 28/10/17
 */
bool Button::contains(float x, float y) const {
    return isEnabled() && isVisible() &&
            (getGlobalBounds().contains(sf::Vector2f(x, y))
            || m_label.getGlobalBounds().contains(sf::Vector2f(x, y)));
}

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin