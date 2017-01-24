#include "Button.h"

/**
 * Constructs a button with coordinates and a size
 * @author Arthur
 * @date 02/01/17
 */
Button::Button(float x, float y, float w, float h) :
        GraphicElement(x, y, w, h), m_currentClipRect{0}, m_labelPosition{CENTER},
        m_isPressed{false}, m_isActive{false}, m_isDisabled{false}
{
    m_font.loadFromFile(RESOURCES_FOLDER + "Roboto_Condensed.ttf");
    m_label = new Text("");
    m_label->setFont(m_font);
    m_label->setColor(sf::Color::White);
    m_label->setPositionSelfCentered(getPosition().x + getGlobalBounds().width/2,
                                     getPosition().y + getGlobalBounds().height/2);
    m_label->setOrigin(0,m_label->getGlobalBounds().height/2);
    m_label->setCharacterSize(24);
}




/**
 * Constructs a button with coordinates,
 * a size and a description
 * @author Arthur
 * @date 02/01/17
 */
Button::Button(float x, float y, float w, float h, std::string description) :
        GraphicElement(x, y, w, h), m_currentClipRect{0}, m_labelPosition{CENTER},
        m_isPressed{false}, m_isActive{false}, m_isDisabled{false}
{
    m_font.loadFromFile(RESOURCES_FOLDER + "Roboto_Condensed.ttf");
    m_label = new Text(description);
    m_label->setFont(m_font);
    m_label->setColor(sf::Color::White);
    m_label->setPositionSelfCentered(getPosition().x + getGlobalBounds().width/2,
                                     getPosition().y + getGlobalBounds().height/2);
    m_label->setOrigin(0,m_label->getGlobalBounds().height/2);
    m_label->setCharacterSize(24);
}


/**
 * Constructs a button with coordinates,
 * a size, a texture and a clipRect
 * @author Arthur
 * @date 6/04/16 - 02/01/17
 */
Button::Button(float x, float y, float w, float h,
               std::string image, const std::vector<sf::IntRect> &clipRect) :
        GraphicElement(x, y, w, h, image), m_clipRectArray{clipRect},
        m_currentClipRect{0},  m_isPressed{false}, m_labelPosition{CENTER},
        m_isActive{false}, m_isDisabled{false}
{
    this->setTextureRect(m_clipRectArray[m_currentClipRect]);

    m_font.loadFromFile(RESOURCES_FOLDER + "Roboto_Condensed.ttf");
    m_label = new Text("");
    m_label->setFont(m_font);
    m_label->setColor(sf::Color::White);
    m_label->setPositionSelfCentered(getPosition().x + getGlobalBounds().width/2,
                                     getPosition().y + getGlobalBounds().height/2);
    m_label->setOrigin(0,m_label->getGlobalBounds().height/2);
    m_label->setCharacterSize(24);
}


/**
 * Constructs a button with coordinates,
 * a size, a texture, a clipRect and a description
 * @author Arthur
 * @date 6/04/16 - 02/01/17
 */
Button::Button(float x, float y, float w, float h, std::string description,
               std::string image, const std::vector<sf::IntRect> &clipRect) :
        GraphicElement(x, y, w, h, image), m_clipRectArray{clipRect},
        m_currentClipRect{0},  m_isPressed{false}, m_labelPosition{CENTER},
        m_isActive{false}, m_isDisabled{false}
{
    this->setTextureRect(m_clipRectArray[m_currentClipRect]);

    m_font.loadFromFile(RESOURCES_FOLDER + "Roboto_Condensed.ttf");
    m_label = new Text(description);
    m_label->setFont(m_font);
    m_label->setColor(sf::Color::White);
    m_label->setPositionSelfCentered(getPosition().x + getGlobalBounds().width/2,
                                     getPosition().y + getGlobalBounds().height/2);
    m_label->setOrigin(0,m_label->getGlobalBounds().height/2);
    m_label->setCharacterSize(24);
}


/**
 * Copy Constructor
 * @author Arthur
 * @date 6/04/16 - 02/01/17
 */
Button::Button(Button const& other) :
        GraphicElement(other), m_clipRectArray{other.m_clipRectArray}, m_currentClipRect{0},
        m_label{other.m_label}, m_labelPosition{other.m_labelPosition},
        m_isPressed{false}, m_isActive{false}, m_isDisabled{false}
{
    this->setTextureRect(m_clipRectArray[m_currentClipRect]);
}


/**
 * Destructor
 * @author Arthur
 * @date 6/04/16 - 07/01/17
 */
Button::~Button()
{
    delete m_label;
}


//=== Getters

bool Button::isDisabled() const { return m_isDisabled; }

//=== Setters

void Button::setPressed(bool state) { m_isPressed = state; }
void Button::setActivated(bool state) { m_isActive = state; }
void Button::setDisabled(bool state) { m_isDisabled = state; }
void Button::setClipRectArray(std::vector<sf::IntRect> crA) { m_clipRectArray = crA; }
void Button::setPositionSelfCentered(double x, double y) {
    setPosition( (float)(x-getGlobalBounds().width/2), (float)y );
}
void Button::setLabelPosition(LabelPosition labelPosition) { m_labelPosition = labelPosition; }


/**
 * Synchronization Function :
 * Changes animation depending on pressed state
 * @author Arthur
 * @date 6/04/16 - 23/12/16
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
 * @date 23/12/16
 */
void Button::sync(DataBase *dataBase)
{
    sync();

    //=== Sync label

    if ( m_label->getDescription() != "")
    {
        m_label->setString(dataBase->getStringFromFile(m_label->getDescription()));

        switch (m_labelPosition) {
            case TOP:
                m_label->setPositionSelfCentered(getPosition().x + getGlobalBounds().width/2,
                                                 getPosition().y - getGlobalBounds().height/2);
                m_label->setOrigin(0,m_label->getGlobalBounds().height/2);
                break;
            case RIGHT:
                m_label->setPosition(getPosition().x + getGlobalBounds().width + 30,
                                     getPosition().y + getGlobalBounds().height/2 - 5);
                m_label->setOrigin(0, m_label->getGlobalBounds().height/2);
                break;
            case BOTTOM:
                m_label->setPositionSelfCentered(getPosition().x + getGlobalBounds().width/2,
                                                 getPosition().y + getGlobalBounds().height + 50);
                m_label->setOrigin(0,m_label->getGlobalBounds().height/2);
                break;
            case LEFT:
                m_label->setPosition((getPosition().x - 30),
                                     getPosition().y+getGlobalBounds().height/2 - 5);
                m_label->setOrigin(m_label->getGlobalBounds().width, m_label->getGlobalBounds().height/2);
                break;
            case CENTER:
                m_label->setPositionSelfCentered(getPosition().x + getGlobalBounds().width/2,
                                                 getPosition().y + getGlobalBounds().height/2);
                m_label->setOrigin(0,m_label->getGlobalBounds().height/2);
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
    if ( isShowing() )
    {
        window->draw(*this);
        window->draw(*m_label);
    }
}

/**
 * Checks if a point of given coordinates is contained
 * in the button or its label
 * @author Arthur
 * @date 23/12/16
 */
bool Button::contains(float x, float y) const {
    return !isDisabled() && isShowing() &&
           (getGlobalBounds().contains(sf::Vector2f(x, y))
            || m_label->getGlobalBounds().contains(sf::Vector2f(x, y)));
}

