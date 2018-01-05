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
 * Destructor
 * @author Arthur, Florian
 * @date 21/02/16 - 29/01/17
 */
AbstractView::~AbstractView() = default;

