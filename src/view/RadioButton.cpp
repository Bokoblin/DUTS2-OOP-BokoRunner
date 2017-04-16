#include "RadioButton.h"

using namespace std;

/**
 * Parameterized Constructor without label description
 * @author Arthur
 * @date 23/12/16 - 02/01/17
 */
RadioButton::RadioButton(float x, float y, float w, float h) :
        Button(x, y, w, h)
{
    setRadioClipRect();
    setTextureFromImage(RADIO_BUTTONS_IMAGE);
}


/**
 * Parameterized Constructor with label description
 * @author Arthur
 * @date 23/12/16 - 02/01/17
 */
RadioButton::RadioButton(float x, float y, float w, float h, const string &label) :
        Button(x, y, w, h, label)
{
    setRadioClipRect();

    if ( label != "indicator")
        setTextureFromImage(RADIO_BUTTONS_IMAGE);
    else
        setTextureFromImage(INDICATOR_IMAGE);
}


/**
 * Copy Constructor
 * @author Arthur
 * @date 02/01/17
 */
RadioButton::RadioButton(RadioButton const& other) : Button(other)
{}


/**
 * Destructor
 * @author Arthur
 * @date 23/12/16
 */
RadioButton::~RadioButton()
{}

/**
 * Synchronization Function : change animation
 * @author Arthur
 * @date 23/12/16
 */
void RadioButton::sync()
{
    if ( !m_isDisabled && m_isActive && !m_isPressed )
        this->setTextureRect(m_clipRectArray[0]);
    if ( !m_isDisabled && m_isActive && m_isPressed )
        this->setTextureRect(m_clipRectArray[1]);
    if ( !m_isDisabled && !m_isActive && !m_isPressed )
        this->setTextureRect(m_clipRectArray[2]);
    if ( !m_isDisabled && !m_isActive && m_isPressed )
        this->setTextureRect(m_clipRectArray[3]);
    if ( m_isDisabled && m_isActive)
        this->setTextureRect(m_clipRectArray[4]);
    if ( m_isDisabled && !m_isActive)
        this->setTextureRect(m_clipRectArray[5]);
}

/**
 * Synchronization Function :
 * Changes animation depending on pressed state
 * sync button's label
 * @author Arthur
 * @date 23/12/16
 */
void RadioButton::sync(DataBase *dataBase)
{
    sync();
    Button::sync(dataBase);
    m_label.setPosition(getPosition().x + 2*getGlobalBounds().width, getPosition().y-3);
    m_label.setOrigin(0, 0);
}


/**
 * Sets default rectangle clips for radios
 * @author Arthur
 * @date 02/01/17
 */
void RadioButton::setRadioClipRect()
{
    vector<sf::IntRect> clipRect;
    clipRect.push_back(sf::IntRect( 0, 0, 50, 50) );
    clipRect.push_back(sf::IntRect( 50, 0, 50, 50) );
    clipRect.push_back(sf::IntRect( 0, 50, 50, 50) );
    clipRect.push_back(sf::IntRect( 50, 50, 50, 50) );
    clipRect.push_back(sf::IntRect( 0, 100, 50, 50) );
    clipRect.push_back(sf::IntRect( 0, 150, 50, 50) );

    setClipRectArray(clipRect);
    setTextureRect(m_clipRectArray[m_currentClipRect]);
}
