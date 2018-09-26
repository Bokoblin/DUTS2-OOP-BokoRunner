#include "Dialog.h"

using std::string;
using Bokoblin::SimpleLogger::Logger;

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
 * @date 16/05/16 - 29/12/17
 */
Dialog::Dialog() : Sprite(0, 0), m_context{""}, m_title{""}, m_content{""},
                   m_cancelButtonText{""}, m_okButtonText{""}
{
    hide();
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
 * @date 02/01/17 - 26/09/18
 */
Dialog::Dialog(float x, float y, float width, float height, const string& context) :
        Sprite(x, y, width, height), m_context{context}, m_title{""}, m_content{""},
        m_cancelButtonText{""}, m_okButtonText{""}
{
    loadAndApplyTextureFromImageFile(Config::DIALOG_IMAGE);
    setPosition(x, y);
    resize(width, height);
    applyColor();

    //=== Initialize text

    m_title.applyTextFont(Config::DEFAULT_BOLD_FONT, 19, sf::Color::Black);
    m_title.setPosition(x + 24, y + 24);

    m_content.applyTextFont(Config::DEFAULT_REGULAR_FONT, 15, sf::Color::Black);
    m_content.setPosition(x + 24, y + height / 3);

    m_cancelButtonText.applyTextFont(Config::DEFAULT_BOLD_FONT, 14, Color::MaterialTeal);
    m_cancelButtonText.setPosition(x + 0.5f * m_width, y + height - 30);

    m_okButtonText.applyTextFont(Config::DEFAULT_BOLD_FONT, 14, Color::MaterialTeal);
    m_okButtonText.setPosition(x + 0.8f * m_width, y + height - 30);
}


/**
 * Destructor
 * @author Arthur
 * @date 16/05/17 - 02/01/17
 */
Dialog::~Dialog() = default;


//------------------------------------------------
//          GETTERS
//------------------------------------------------

const string& Dialog::getContext() const { return m_context; }
const Text& Dialog::getCancelButtonText() const { return m_cancelButtonText; }
const Text& Dialog::getOkButtonText() const { return m_okButtonText; }


//------------------------------------------------
//          SETTERS
//------------------------------------------------

void Dialog::setTitleText(const string& title) { m_title.setString(title); }
void Dialog::setContentText(const string& content) { m_content.setString(content);}
void Dialog::setCancelButtonText(const string& cancel) { m_cancelButtonText.setString(cancel); };
void Dialog::setOkButtonText(const string& ok) { m_okButtonText.setString(ok); }


//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Draws the dialog (background and components)
 *
 * @param window the app's window
 *
 * @author Arthur
 * @date 16/05/16 - 02/01/17
 */
void Dialog::draw(sf::RenderWindow* window) const
{
    if (isVisible()) {
        window->draw(*this);
        window->draw(m_title);
        window->draw(m_content);
        window->draw(m_cancelButtonText);
        window->draw(m_okButtonText);
    }
}

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin
