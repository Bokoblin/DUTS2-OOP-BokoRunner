#include "AbstractView.h"

/**
 * Parameterized Constructor called
 * by the inherited classes
 *
 * @author Arthur, Florian
 * @date 29/01/17
 *
 * @param window the app's window
 * @param textHandler a text handler
 */
AbstractView::AbstractView(sf::RenderWindow *window, TextHandler *textHandler) :
    m_window{window}, m_textHandler{textHandler}
{
    m_width = m_window->getSize().x;
    m_height = m_window->getSize().y;

    m_window->setFramerateLimit(FRAMERATE);
}


/**
 * Parameterized Constructor called
 * by the inherited classes
 *
 * @author Arthur, Florian
 * @date 21/02/16 - 29/01/17
 *
 * @param width the app's width
 * @param height the app's height
 * @param window the app's window
 * @param textHandler a text handler
 *
 * @deprecated will me removed for 2.0 release if not used - TODO
 */
[[deprecated]]
AbstractView::AbstractView(float width, float height, sf::RenderWindow *window, TextHandler *textHandler) :
    m_width{width}, m_height{height}, m_window{window}, m_textHandler{textHandler}
{}


/**
 * Destructor
 * @author Arthur, Florian
 * @date 21/02/16 - 29/01/17
 */
AbstractView::~AbstractView() {}

