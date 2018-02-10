#include "AbstractView.h"

//------------------------------------------------
//          CONSTRUCTORS / DESTRUCTOR
//------------------------------------------------

/**
 * Parameterized Constructor called
 * by the inherited classes with a window and a text manager
 *
 * @param window the app's window
 * @param textManager a text manager
 *
 * @author Arthur, Florian
 * @date 29/01/17
 */
AbstractView::AbstractView(sf::RenderWindow *window, AppTextManager *textManager) :
    m_window{window}, m_textManager{textManager}
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

