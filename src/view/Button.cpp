#include "Button.h"

/**
 * Constructs a button with coordinates and a size
 * @author Arthur
 * @date 02/01/17 - 28/10/17
 */
Button::Button(float x, float y, float w, float h) :
        GraphicElement(x, y, w, h), m_currentClipRect{0}, m_labelPosition{CENTER},
        m_isPressed{false}, m_isSelected{false}, m_isEnabled{true}, m_label{""}
{
    m_font.loadFromFile(ROBOTO_CONDENSED_FONT);
    m_label.setFont(m_font);
    m_label.setFillColor(sf::Color::White);
    m_label.setPositionSelfCentered(getPosition().x + getGlobalBounds().width/2,
                                     getPosition().y + getGlobalBounds().height/2);
    m_label.setOrigin(0, m_label.getGlobalBounds().height/2);
    m_label.setCharacterSize(22);
}




/**
 * Constructs a button with coordinates,
 * a size and a description
 * @author Arthur
 * @date 02/01/17 - 28/10/17
 */
Button::Button(float x, float y, float w, float h, const std::string &description) :
        GraphicElement(x, y, w, h), m_currentClipRect{0}, m_labelPosition{CENTER},
        m_isPressed{false}, m_isSelected{false}, m_isEnabled{true}, m_label{description}
{
    m_font.loadFromFile(ROBOTO_CONDENSED_FONT);
    m_label.setFont(m_font);
    m_label.setFillColor(sf::Color::White);
    m_label.setPositionSelfCentered(getPosition().x + getGlobalBounds().width/2,
                                     getPosition().y + getGlobalBounds().height/2);
    m_label.setOrigin(0, m_label.getGlobalBounds().height/2);
    m_label.setCharacterSize(22);
}


/**
 * Constructs a button with coordinates,
 * a size, a texture and a clipRect
 * @author Arthur
 * @date 06/04/16 - 28/10/17
 */
Button::Button(float x, float y, float w, float h,
               const std::string &image, const std::vector<sf::IntRect> &clipRect) :
        GraphicElement(x, y, w, h, image), m_clipRectArray{clipRect},
        m_currentClipRect{0},  m_isPressed{false}, m_labelPosition{CENTER},
        m_isSelected{false}, m_isEnabled{true}, m_label{""}
{
    this->setTextureRect(m_clipRectArray[m_currentClipRect]);

    m_font.loadFromFile(ROBOTO_CONDENSED_FONT);
    m_label.setFont(m_font);
    m_label.setFillColor(sf::Color::White);
    m_label.setPositionSelfCentered(getPosition().x + getGlobalBounds().width/2,
                                     getPosition().y + getGlobalBounds().height/2);
    m_label.setOrigin(0, m_label.getGlobalBounds().height/2);
    m_label.setCharacterSize(22);
}


/**
 * Constructs a button with coordinates,
 * a size, a texture, a clipRect and a description
 * @author Arthur
 * @date 06/04/16 - 28/10/17
 */
Button::Button(float x, float y, float w, float h, const std::string &description,
               const std::string &image, const std::vector<sf::IntRect> &clipRect) :
        GraphicElement(x, y, w, h, image), m_clipRectArray{clipRect},
        m_currentClipRect{0},  m_isPressed{false}, m_labelPosition{CENTER},
        m_isSelected{false}, m_isEnabled{true}, m_label{description}
{
    this->setTextureRect(m_clipRectArray[m_currentClipRect]);

    m_font.loadFromFile(ROBOTO_CONDENSED_FONT);
    m_label.setFont(m_font);
    m_label.setFillColor(sf::Color::White);
    m_label.setPositionSelfCentered(getPosition().x + getGlobalBounds().width/2,
                                     getPosition().y + getGlobalBounds().height/2);
    m_label.setOrigin(0, m_label.getGlobalBounds().height/2);
    m_label.setCharacterSize(22);
}


/**
 * Copy Constructor
 * @author Arthur
 * @date 06/04/16 - 02/01/17
 */
Button::Button(Button const& other) :
        GraphicElement(other), m_clipRectArray{other.m_clipRectArray}, m_currentClipRect{0},
        m_label{other.m_label}, m_labelPosition{other.m_labelPosition},
        m_isPressed{false}, m_isSelected{false}, m_isEnabled{true}
{
    this->setTextureRect(m_clipRectArray[m_currentClipRect]);
}


/**
 * Destructor
 * @author Arthur
 * @date 06/04/16 - 25/01/17
 */
Button::~Button()
{}


//=== Getters

bool Button::isEnabled() const { return m_isEnabled; }

//=== Setters

void Button::setPressed(bool pressed) { m_isPressed = pressed; }
void Button::setSelected(bool selected) { m_isSelected = selected; }
void Button::setEnabled(bool enabled) { m_isEnabled = enabled; }
void Button::setClipRectArray(std::vector<sf::IntRect> array) { m_clipRectArray = array; }
void Button::setPositionSelfCentered(double x, double y) {
    setPosition((float)(x-getGlobalBounds().width/2), (float)y);
}
void Button::setLabelPosition(LabelPosition labelPosition) { m_labelPosition = labelPosition; }


/**
 * Synchronization Function :
 * Changes animation depending on pressed state
 * @author Arthur
 * @date 06/04/16 - 23/12/16
 */
void Button::sync()
{
    this->setTextureRect(m_clipRectArray[m_isPressed]);
}

/**
 * Synchronization Function :
 * Changes animation depending on pressed state
 * sync button's label
 * @author Arthur
 * @date 23/12/16 - 25/01/17
 */
void Button::sync(DataBase *dataBase)
{
    sync();

    //=== Sync label

    if (m_label.getDescription() != "")
    {
        std::string utf8_string = dataBase->getTextValueFromStringsFile(m_label.getDescription());
        m_label.setString(sf::String::fromUtf8(utf8_string.begin(), utf8_string.end()));

        switch (m_labelPosition)
        {
            case TOP:
                m_label.setPositionSelfCentered(getPosition().x + getGlobalBounds().width/2,
                                                 getPosition().y - getGlobalBounds().height/2);
                m_label.setOrigin(0, m_label.getGlobalBounds().height/2);
                break;
            case RIGHT:
                m_label.setPosition(getPosition().x + getGlobalBounds().width + 30,
                                     getPosition().y + getGlobalBounds().height/2 - 7);
                m_label.setOrigin(0, m_label.getGlobalBounds().height/2);
                break;
            case BOTTOM:
                m_label.setPositionSelfCentered(getPosition().x + getGlobalBounds().width/2,
                                                 getPosition().y + getGlobalBounds().height + 50);
                m_label.setOrigin(0, m_label.getGlobalBounds().height/2);
                break;
            case LEFT:
                m_label.setPosition((getPosition().x - 30),
                                     getPosition().y+getGlobalBounds().height/2 - 7);
                m_label.setOrigin(m_label.getGlobalBounds().width, m_label.getGlobalBounds().height/2);
                break;
            case CENTER:
                m_label.setPositionSelfCentered(getPosition().x + getGlobalBounds().width/2,
                                                 getPosition().y + getGlobalBounds().height/2);
                m_label.setOrigin(0, m_label.getGlobalBounds().height/2);
                break;
        }
    }
}


/**
 * Draws the button and its label
 * @author Arthur
 * @date 23/12/16
 */
void Button::draw(sf::RenderWindow *window) const
{
    if (isVisible())
    {
        window->draw(*this);
        window->draw(m_label);
    }
}

/**
 * Checks if a point of given coordinates is contained
 * in the button or its label
 * @author Arthur
 * @date 23/12/16 - 28/10/17
 */
bool Button::contains(float x, float y) const {
    return isEnabled() && isVisible() &&
           (getGlobalBounds().contains(sf::Vector2f(x, y))
            || m_label.getGlobalBounds().contains(sf::Vector2f(x, y)));
}

