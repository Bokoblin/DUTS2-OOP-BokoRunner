#include "../header/View.h"

using namespace std;

/********************************************
    Parameterized Constructor
*********************************************
    @author Arthur  @date 21/02 - 27/03
    @author Florian @date 21/02 - 3/03
*********************************************/
View::View(float w, float h, sf::RenderWindow *window):
    m_width(w), m_height(h), m_window{window}
{
    m_text = new Text();
}


/********************************************
    Destructor
*********************************************
    @author Arthur  @date 21/02 - 27/03
    @author Florian  @date 21/02 - 2/03
*********************************************/
View::~View()
{}


/********************************************
   Getters
*********************************************
    @author Arthur  @date 27/03
*********************************************/
sf::RenderWindow* View::getWindow() { return m_window; }


/********************************************
   Setters
*********************************************
    @author Arthur  @date 21/02
    @author Florian @date 21/02
*********************************************/
void View::setModel(Model *model) { m_model = model; }
