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

Dialog::Dialog() : Sprite(0, 0), m_context{""}, m_title{""}, m_content{""},
                   m_cancelButtonText{""}, m_okButtonText{""}
{
    hide();
}


/**
 * Constructs a dialog with x and y coordinates,
 * a textHandler and a description
 * @author Arthur
 * @date 02/01/2017 - 07/01/17
 */
Dialog::Dialog(float x, float y, float w, float h, const string &context) :
        Sprite(x, y, w, h), m_context{context}, m_title{""}, m_content{""},
        m_cancelButtonText{""}, m_okButtonText{""}
{
    setTextureFromImage(DIALOG_IMAGE);
    setPosition(x, y);
    resize(w, h);

    //=== Initialize text

    m_title.applyTextFont(Config::DEFAULT_BOLD_FONT, 19, sf::Color::Black);
    m_title.setPosition(x + 24, y + 24);

    m_content.applyTextFont(Config::DEFAULT_REGULAR_FONT, 15, sf::Color::Black);
    m_content.setPosition(x + 24, y + h/3);

    m_cancelButtonText.applyTextFont(Config::DEFAULT_BOLD_FONT, 14, Color::MaterialTeal);
    m_cancelButtonText.setPosition((float) (x + 0.5*m_width), y + h - 30);

    m_okButtonText.applyTextFont(Config::DEFAULT_BOLD_FONT, 14, Color::MaterialTeal);
    m_okButtonText.setPosition((float) (x + 0.8*m_width), y + h - 30);
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

//=== Setters
void Dialog::setTitleText(const string &title) { m_title.setString(title); }
void Dialog::setContentText(const string &content) { m_content.setString(content);}
void Dialog::setCancelButtonText(const string &cancel) { m_cancelButtonText.setString(cancel); };
void Dialog::setOkButtonText(const string &ok) { m_okButtonText.setString(ok); }


//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Draw function
 * @author Arthur
 * @date 16/05/16 - 02/01/17
 */
void Dialog::draw(sf::RenderWindow *window) const
{
    if (isVisible())
    {
        window->draw(*this);
        window->draw(m_title);
        window->draw(m_content);
        window->draw(m_cancelButtonText);
        window->draw(m_okButtonText);
    }
}

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin
