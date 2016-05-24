#include "LeaderboardView.h"

using namespace std;


/********************************************
    Parameterized Constructor
*********************************************
    @author Arthur  @date 21/05
*********************************************/
LeaderboardView::LeaderboardView(float w, float h, sf::RenderWindow *window, Text * t):
    View(w, h, window, t), m_leaderboard{nullptr}
{
	    loadImages();
}


/********************************************
    Destructor
*********************************************
    @author Arthur  @date 21/05
*********************************************/
LeaderboardView::~LeaderboardView()
{
    delete m_homeFormButton;
    delete m_clearLbRectButton;
}


/********************************************
   Setters
*********************************************
    @author Arthur  @date 20/05
*********************************************/
void LeaderboardView::setLeaderboardModel(Leaderboard *model)
{
    m_leaderboard = model;
}


/********************************************
    Image Loading
*********************************************
    @author Arthur  @date 20/05
*********************************************/
void LeaderboardView::loadImages()
{
    //=== Initialize CLEAR button

	if (!m_rectButtonsTexture.loadFromFile(MENU_RECT_BUTTONS_IMAGE) )
		cerr << "ERROR when loading image file: " << MENU_RECT_BUTTONS_IMAGE << endl;
	else
	{
        m_rectButtonsTexture.setSmooth(true);

        vector<sf::IntRect> clip_rects;
		clip_rects.push_back(sf::IntRect( 0, 100, 150, 40));
		clip_rects.push_back(sf::IntRect(151, 100, 150, 40));
        m_clearLbRectButton = new Button(clip_rects, m_rectButtonsTexture, m_width/2-75, 500, 150, 40, false);
    }

    //=== Initialize HOME form button

    if (!m_menuButtonTexture.loadFromFile(FORM_BUTTONS_IMAGE) )
        cerr << "ERROR when loading image file: " << FORM_BUTTONS_IMAGE << endl;
    else
    {
        m_menuButtonTexture.setSmooth(true);

        std::vector<sf::IntRect> clip_rects;
        clip_rects.push_back(sf::IntRect( 0, 50, 50, 50));
        clip_rects.push_back(sf::IntRect( 51, 50, 50, 50));
        m_homeFormButton = new Button(clip_rects, m_menuButtonTexture, 10, 10, 50, 50, false);
     }
}


/********************************************
    Synchronization function
*********************************************
    @author Arthur  @date 20/05 - 21/05
*********************************************/
void LeaderboardView::synchronize()
{
    //=== Elements update

    m_homeFormButton->sync();
    m_clearLbRectButton->sync();
    m_clearLbRectButton->setPosition(m_width/2 -
    m_clearLbRectButton->HALF_WIDTH, 540);
    m_homeFormButton->resize(FORM_BUTTONS_SIZE);

    //=== Text update

    m_text->syncMenuLeaderboardText(m_width, m_height, m_leaderboard);
}


/********************************************
    LeaderboardView Drawing
*********************************************
    @author Arthur  @date 21/05
*********************************************/
void LeaderboardView::draw() const
{
    m_window->clear( GREY_BG_COLOR );

    //=== Graphic Elements drawing

    m_window->draw(*m_homeFormButton);
    m_window->draw(*m_clearLbRectButton);

    //=== Text Drawing

    m_text->drawLeaderboardText(m_window);
    m_window->display();
}


/********************************************
    Events treating
*********************************************
    @author Arthur  @date 21/05
*********************************************/
bool LeaderboardView::treatEvents() { return false; }
bool LeaderboardView::treatEvents(sf::Event event)
{
    bool stop_leaderboard = false;

    if (MOUSE_LEFT_PRESSED_EVENT)
    {
        if ( m_homeFormButton->IS_POINTED )
            m_homeFormButton->setPressedState(true);

        if ( m_clearLbRectButton->IS_POINTED )
            m_clearLbRectButton->setPressedState(true);
    }

    if (event.type == sf::Event::MouseButtonReleased)
    {
        //=== Reset buttons

        m_homeFormButton->setPressedState(false);
        m_clearLbRectButton->setPressedState(false);

        //=== handle mouse up on a button

        if ( m_homeFormButton->IS_POINTED )
        {
            stop_leaderboard = true;
        }
        if ( m_clearLbRectButton->IS_POINTED )
        {
            m_leaderboard->createFile();
        }
    }
    return stop_leaderboard;
}