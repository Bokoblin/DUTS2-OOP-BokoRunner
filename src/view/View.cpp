#include "View.h"

using namespace std;

/**
 * Parameterized Constructor
 * @author Arthur, Florian
 * @date 21/02/16 - 14/03/16
 */
View::View(float w, float h, sf::RenderWindow *window, TextHandler *text):
    m_width(w), m_height(h), m_window{window}, m_textHandler{text}, m_model{nullptr}
{}


/**
 * Destructor
 * @author Arthur, Florian
 * @date 21/02/16 - 27/03/16
 */
View::~View() = default;


/**
 * Setters
 * @author Arthur, Florian
 * @date 21/02/16
 */
void View::setModel(Model *model) { m_model = model; }
