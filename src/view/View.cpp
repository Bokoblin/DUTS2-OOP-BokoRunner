#include "View.h"

using namespace std;

/********************************************
    Parameterized Constructor
*********************************************
    @author Arthur  @date 21/02 - 14/03
    @author Florian @date 21/02 - 3/03
*********************************************/
View::View(float w, float h, sf::RenderWindow *window, Text *text):
    m_width(w), m_height(h), m_window{window}, m_text{text}, m_model{nullptr}
{}


/********************************************
    Destructor
*********************************************
    @author Arthur  @date 21/02 - 27/03
    @author Florian  @date 21/02 - 2/03
*********************************************/
View::~View()
{}


/********************************************
   Setters
*********************************************
    @author Arthur  @date 21/02
    @author Florian @date 21/02
*********************************************/
void View::setModel(Model *model) { m_model = model; }
