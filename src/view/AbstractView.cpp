#include "AbstractView.h"

using namespace std;

/**
 * Parameterized Constructor called
 * by the inherited classes
 *
 * @author Arthur, Florian
 * @date 21/02 - 26/12
 */
AbstractView::AbstractView(int w, int h, sf::RenderWindow *window, TextHandler *text):
    m_width(w), m_height(h), m_window{window}, m_textHandler{text}
{}

AbstractView::AbstractView(int w, int h, sf::RenderWindow *window,
                           TextHandler *text, AbstractModel *model):
    m_width(w), m_height(h), m_window{window}, m_textHandler{text}
{}


/**
 * Destructor
 * @author Arthur, Florian
 * @date 21/02 - 27/03
 */
AbstractView::~AbstractView() {}

