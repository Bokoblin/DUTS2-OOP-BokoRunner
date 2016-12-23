#include "RadioButton.h"

/**
 * Parameterized Constructor without label description
 * @author Arthur
 * @date 23/12
 */
RadioButton::RadioButton(const std::vector<sf::IntRect> & clipRect,
                         sf::Texture &image, float x, float y, float w, float h):
        Button( clipRect, image, x, y, w, h, "")
{}

/**
 * Parameterized Constructor with label description
 * @author Arthur
 * @date 23/12
 */
RadioButton::RadioButton(const std::vector<sf::IntRect> & clipRect,
                         sf::Texture &image, float x, float y, float w, float h, std::string label):
        Button( clipRect, image, x, y, w, h, label)
{}


/**
 * Destructor
 * @author Arthur
 * @date 23/12
 */
RadioButton::~RadioButton()
{}

/**
 * Synchronization Function : change animation
 * @author Arthur
 * @date 23/12
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
 * @date 23/12
 */
void RadioButton::sync(DataBase *dataBase)
{
    sync();

    //=== Sync label

    Button::sync(dataBase);

    m_label->setPosition(getPosition().x + 2*getGlobalBounds().width, getPosition().y-3);
    m_label->setOrigin(0, 0);
}