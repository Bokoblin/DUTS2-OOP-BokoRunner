#include "LeaderboardView.h"

using namespace std;


/**
 * Parameterized Constructor
 * @author Arthur
 * @date 21/05
 */
LeaderboardView::LeaderboardView(float w, float h, sf::RenderWindow *window, TextHandler * t):
    View(w, h, window, t), m_leaderboard{nullptr}
{
    loadImages();
    m_textHandler->syncMenuLeaderboardText();
}


/**
 * Destructor
 * @author Arthur
 * @date 21/05
 */
LeaderboardView::~LeaderboardView()
{
    delete m_homeFormButton;
    delete m_clearLbRectButton;
}


//=== Setters

void LeaderboardView::setLeaderboardModel(Leaderboard *model)
{
    m_leaderboard = model;
}


/**
 * Image Loading
 * @author Arthur
 * @date 20/05
 */
void LeaderboardView::loadImages()
{
    //=== Initialize CLEAR button

	if (!m_rectButtonsTexture.loadFromFile(MENU_RECT_BUTTONS_IMAGE) )
		cerr << "ERROR when loading image file: " << MENU_RECT_BUTTONS_IMAGE << endl;
	else
	{
        m_rectButtonsTexture.setSmooth(true);

        vector<sf::IntRect> clipRect;
		clipRect.push_back(sf::IntRect( 0, 100, 150, 40));
		clipRect.push_back(sf::IntRect(151, 100, 150, 40));
        m_clearLbRectButton = new Button(clipRect, m_rectButtonsTexture, m_width/2-75, 500, 150, 40, false);
    }

    //=== Initialize HOME form button

    if (!m_menuButtonTexture.loadFromFile(FORM_BUTTONS_IMAGE) )
        cerr << "ERROR when loading image file: " << FORM_BUTTONS_IMAGE << endl;
    else
    {
        m_menuButtonTexture.setSmooth(true);

        std::vector<sf::IntRect> clipRect;
        clipRect.push_back(sf::IntRect( 0, 50, 50, 50));
        clipRect.push_back(sf::IntRect( 51, 50, 50, 50));
        m_homeFormButton = new Button(clipRect, m_menuButtonTexture, 10, 10, 50, 50, false);
     }
}


/**
 * Synchronization function
 * @author Arthur
 * @date 20/05 - 24/10
 */
void LeaderboardView::synchronize()
{
    //=== Elements update

    m_homeFormButton->sync();
    m_clearLbRectButton->sync();
    m_clearLbRectButton->setPosition(m_width/2 - m_clearLbRectButton->getGlobalBounds().width/2, 540);
    m_homeFormButton->resize(FORM_BUTTONS_SIZE);
}


/**
 * LeaderboardView Drawing
 * @author Arthur
 * @date 21/05
 */
void LeaderboardView::draw() const
{
    m_window->clear( GREY_BG_COLOR );

    //=== Graphic Elements drawing

    m_window->draw(*m_homeFormButton);
    m_window->draw(*m_clearLbRectButton);

    //=== TextHandler Drawing

    m_textHandler->drawLeaderboardText(m_window);
    m_window->display();
}


/**
 * Events treating
 * @author Arthur
 * @date 21/05
 */
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
            m_leaderboard->getDataBase()->resetScore();
            m_textHandler->syncMenuLeaderboardText();
        }
    }
    return stop_leaderboard;
}
