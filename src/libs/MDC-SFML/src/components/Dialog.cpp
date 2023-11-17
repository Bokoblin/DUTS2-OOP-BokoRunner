#include "Dialog.h"

using std::string;

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{
//------------------------------------------------
//          CONSTRUCTORS / DESTRUCTOR
//------------------------------------------------

/**
 * Constructs an empty dialog
 *
 * @author Arthur
 * @date 16/05/2016 - 28/06/2020
 */
Dialog::Dialog() : AbstractShapeMaterial(0, 0, 999, 5),
                   m_context{""}, m_title{""}, m_content{""},
                   m_cancelButtonText{""}, m_okButtonText{""}
{
    m_states[VISIBLE] = false;
}


/**
 * Constructs a dialog with coordinates,
 * a size and a context string
 *
 * @param x the x-axis coordinate
 * @param y the y-axis coordinate
 * @param width the width
 * @param height the height
 * @param context the context to make a contextual dialog
 *
 * @author Arthur
 * @date 02/01/2017 - 26/09/2018
 */
Dialog::Dialog(float x, float y, float width, float height, const string& context) :
        AbstractShapeMaterial(width, height, 999, 0),
        m_context{context}, m_title{""}, m_content{""},
        m_cancelButtonText{""}, m_okButtonText{""}
{
    m_shape.setPosition(x, y);
    m_shape.setFillColor(m_fillColor); //FIXME:nope
    m_shape.setFillColor(m_outlineColor);
    Dialog::resize(width, height); //TODO: à faire dans le sync en ayant stocké la taille actuelle

    //=== Initialize text

    m_title.applyTextFont(Config::DEFAULT_BOLD_FONT, 19, sf::Color::Black);
    m_title.setPosition(x + 24, y + 24);

    m_content.applyTextFont(Config::DEFAULT_REGULAR_FONT, 15, sf::Color::Black);
    m_content.setPosition(x + 24, y + height / 3);

    m_cancelButtonText.applyTextFont(Config::DEFAULT_BOLD_FONT, 14, Color::MaterialTeal);
    m_cancelButtonText.setPosition(x + 0.5f * getSize().x, y + height - 30);

    m_okButtonText.applyTextFont(Config::DEFAULT_BOLD_FONT, 14, Color::MaterialTeal);
    m_okButtonText.setPosition(x + 0.8f * getSize().y, y + height - 30);
}


/**
 * Destructor
 * @author Arthur
 * @date 16/05/2017 - 02/01/2017
 */
Dialog::~Dialog() = default;


//------------------------------------------------
//          GETTERS
//------------------------------------------------
float Dialog::getX() const {return m_shape.getPosition().x; }
float Dialog::getY() const {return m_shape.getPosition().y; }
const string& Dialog::getContext() const { return m_context; }
const Text& Dialog::getCancelButtonText() const { return m_cancelButtonText; }
const Text& Dialog::getOkButtonText() const { return m_okButtonText; }


//------------------------------------------------
//          SETTERS
//------------------------------------------------

void Dialog::setTitleText(const string& title) { m_title.setString(title); }
void Dialog::setContentText(const string& content) { m_content.setString(content); }
void Dialog::setCancelButtonText(const string& cancel) { m_cancelButtonText.setString(cancel); }
void Dialog::setOkButtonText(const string& ok) { m_okButtonText.setString(ok); }


//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Updates the dialog coloration
 * @author Arthur
 * @date 28/06/2020
 */
void Dialog::sync()
{
    AbstractShapeMaterial::sync();
    m_shape.setFillColor(m_fillColor);
    m_shape.setOutlineColor(m_outlineColor);

    //TODO: Image generation old test with pixels
    sf::Uint8 pixels[4];
    pixels[0] = 0;   // composante rouge
    pixels[1] = 255; // composante verte
    pixels[2] = 0;   // composante rouge
    pixels[3] = 255; // composante alpha
    auto *t = const_cast<sf::Texture*>(m_shape.getTexture());
    t->update(pixels, 1, 1, 5, 5);
    t->update(pixels, 1, 1, 5, 6);
    t->update(pixels, 1, 1, 5, 8);
    m_shape.setTexture(t);
}

/**
 * Draws the dialog (background and components)
 *
 * @param window the app's window
 *
 * @author Arthur
 * @date 16/05/2016 - 02/01/2017
 */
void Dialog::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (isVisible()) {
        target.draw(m_shape, states);
        target.draw(m_title, states);
        target.draw(m_content, states);
        target.draw(m_cancelButtonText, states);
        target.draw(m_okButtonText, states);
    }
}

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin
