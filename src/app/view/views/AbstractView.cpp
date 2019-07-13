#include "AbstractView.h"

namespace ViewResources = Bokoblin::BokoRunner::Resources::View;

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
AbstractView::AbstractView(sf::RenderWindow* window, AppTextManager* textManager) :
        m_window{window}, m_textManager{textManager}
{
    m_width = m_window->getSize().x;
    m_height = m_window->getSize().y;

    m_window->setFramerateLimit(ViewResources::APP_FRAMERATE);
}

/**
 * Return the half position on the X axis
 * @return an unsigned integer
 */
unsigned int AbstractView::getHalfXPosition() const
{
    return m_width / 2;
}

/**
 * Return the half position on the Y axis
 * @return an unsigned integer
 */
unsigned int AbstractView::getHalfYPosition() const
{
    return m_height / 2;
}


/**
 * Destructor
 * @author Arthur, Florian
 * @date 21/02/16 - 29/01/17
 */
AbstractView::~AbstractView() = default;

