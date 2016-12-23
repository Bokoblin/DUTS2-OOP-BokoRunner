#include "Button.h"

/**
 * Parameterized Constructor without label description
 * @author Arthur
 * @date 6/04 - 23/12
 */
Button::Button(const std::vector<sf::IntRect> & clipRect,
               sf::Texture &image, float x, float y, float w, float h):
            GraphicElement(image, x, y, w, h), m_clipRectArray{clipRect},
            m_currentClipRect{0},  m_isPressed{false}, m_labelPosition{CENTER},
            m_isActive{false}, m_isDisabled{false}, m_isVisible{true}
{
    this->setTextureRect(m_clipRectArray[m_currentClipRect]);

    m_font.loadFromFile(RESOURCES_FOLDER + "Roboto_Condensed.ttf");
    m_label = new Text();
    m_label->setFont(m_font);
    m_label->setColor(sf::Color::White);
    m_label->setPositionSelfCentered(getPosition().x + getGlobalBounds().width/2,
                                    getPosition().y + getGlobalBounds().height/2);
    m_label->setOrigin(0,m_label->getGlobalBounds().height/2);
    m_label->setCharacterSize(24);
}

/**
 * Parameterized Constructor with label description
 * @author Arthur
 * @date 6/04 - 23/12
 */
Button::Button(const std::vector<sf::IntRect> & clipRect, sf::Texture &image,
               float x, float y, float w, float h, std::string labelDescription):
        GraphicElement(image, x, y, w, h), m_clipRectArray{clipRect},
        m_currentClipRect{0},  m_isPressed{false}, m_labelPosition{CENTER},
        m_isActive{false}, m_isDisabled{false}, m_isVisible{true}
{
    this->setTextureRect(m_clipRectArray[m_currentClipRect]);

    m_font.loadFromFile(RESOURCES_FOLDER + "Roboto_Condensed.ttf");
    m_label = new Text(labelDescription);
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
 * @date 6/04 - 23/12
 */
Button::Button(Button const& other) :
    GraphicElement(other), m_clipRectArray{other.m_clipRectArray}, m_currentClipRect{0},
    m_label{other.m_label}, m_labelPosition{other.m_labelPosition},
    m_isPressed{false}, m_isActive{false}, m_isDisabled{false}, m_isVisible{true}
{
    this->setTextureRect(m_clipRectArray[m_currentClipRect]);
}


/**
 * Destructor
 * @author Arthur
 * @date 6/04 - 23/12
 */
Button::~Button()
{}


//=== Getters

bool Button::isDisabled() const { return m_isDisabled; }
bool Button::isVisible() const { return m_isVisible; }

//=== Setters

void Button::setPressed(bool state) { m_isPressed = state; }
void Button::setActivated(bool state) { m_isActive = state; }
void Button::setDisabled(bool state) { m_isDisabled = state; }
void Button::setVisible(bool on) { m_isVisible = on; }
void Button::setClipRectArray(std::vector<sf::IntRect> crA) { m_clipRectArray = crA; }
void Button::setPositionSelfCentered(double x, double y) {
    setPosition( (float)(x-getGlobalBounds().width/2), (float)y );
}
void Button::setLabelPosition(LabelPosition labelPosition) { m_labelPosition = labelPosition; }


/**
 * Synchronization Function :
 * Changes animation depending on pressed state
 * @author Arthur
 * @date 6/04 - 23/12
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
 * @date 23/12
 */
void Button::sync(DataBase *dataBase)
{
    sync();

    //=== Sync label

    if ( m_label->getDescription() != "")
    {
        std::string file;

        if ( dataBase->getLanguage() == "en")
            file = ENGLISH_STRINGS;
        else if ( dataBase->getLanguage() == "fr")
            file = FRENCH_STRINGS;
        else if ( dataBase->getLanguage() == "es")
            file = SPANISH_STRINGS;

        pugi::xml_document doc;
        doc.load_file(file.c_str());

        pugi::xml_node resources = doc.child("resources");

        for (pugi::xml_node item: resources.children("string"))
        {
            if (std::string(item.attribute("name").value()) == m_label->getDescription())
            {
                m_label->setString(item.attribute("value").value());
                break;
            }
        }

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
 * @date 23/12
 */
void Button::draw(sf::RenderWindow *window) const
{
    if ( isVisible())
    {
        window->draw(*this);
        window->draw(*m_label);
    }
}

/**
 * Checks if a point of given coordinates is contained
 * in the button or its label
 * @author Arthur
 * @date 23/12
 */
bool Button::contains(float posX, float posY) const {
    return !isDisabled() && isVisible() && (getGlobalBounds().contains(sf::Vector2f(posX, posY))
                                               || m_label->getGlobalBounds().contains(sf::Vector2f(posX, posY)));
}

