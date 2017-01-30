#include "LeaderboardView.h"

using namespace std;


/**
 * Parameterized Constructor
 * @author Arthur
 * @date 21/05/16 - 29/01/17
 */
LeaderboardView::LeaderboardView(sf::RenderWindow *window, TextHandler *textHandler, Leaderboard *leaderboardModel) :
        AbstractView(window, textHandler), m_leaderboard{leaderboardModel}
{
    loadImages();
}


/**
 * Destructor
 * @author Arthur
 * @date 21/05/16
 */
LeaderboardView::~LeaderboardView()
{
    delete m_homeFormButton;
    delete m_clearLbRectButton;
}


/**
 * Image Loading
 * @author Arthur
 * @date 20/05/16 - 02/01/17
 */
void LeaderboardView::loadImages()
{
    //=== Initialize CLEAR button

    vector<sf::IntRect> clipRect_clear;
    clipRect_clear.push_back(sf::IntRect( 0, 100, 150, 40));
    clipRect_clear.push_back(sf::IntRect(151, 100, 150, 40));
    m_clearLbRectButton = new Button(m_width / 2 - 75, 540, 150, 40, "leaderboard_clear_button",
                                     RECT_BUTTONS_IMAGE, clipRect_clear);

    //=== Initialize HOME form button

    std::vector<sf::IntRect> clipRect_home;
    clipRect_home.push_back(sf::IntRect( 0, 50, 50, 50));
    clipRect_home.push_back(sf::IntRect( 51, 50, 50, 50));
    m_homeFormButton = new Button(10, 10, 50, 50, SHAPE_BUTTONS_IMAGE, clipRect_home);
}


/**
 * Synchronization function
 * @author Arthur
 * @date 20/05/16 - 29/01/17
 */
void LeaderboardView::synchronize()
{
    m_homeFormButton->sync();
    m_homeFormButton->resize(FORM_BUTTONS_SIZE);
    m_clearLbRectButton->sync(m_leaderboard->getDataBase());

    m_textHandler->syncMenuLeaderboardText();
}


/**
 * LeaderboardView Drawing
 * @author Arthur
 * @date 21/05/16 - 23/12/16
 */
void LeaderboardView::draw() const
{
    m_window->clear( MINE_GREY_COLOR );

    //=== Graphic Elements drawing

    m_window->draw(*m_homeFormButton);
    m_clearLbRectButton->draw(m_window);

    //=== TextHandler Drawing

    m_textHandler->drawLeaderboardText(m_window);
    m_window->display();
}


/**
 * Events treating
 * @author Arthur
 * @date 21/05/16 - 23/12/16
 */
bool LeaderboardView::treatEvents(sf::Event event)
{
    bool stop_leaderboard = false;

    if (MOUSE_LEFT_PRESSED_EVENT)
    {
        if (m_homeFormButton->contains(MOUSE_POSITION) )
            m_homeFormButton->setPressed(true);

        if (m_clearLbRectButton->contains(MOUSE_POSITION) )
            m_clearLbRectButton->setPressed(true);
    }

    if (event.type == sf::Event::MouseButtonReleased)
    {
        //=== Reset buttons

        m_homeFormButton->setPressed(false);
        m_clearLbRectButton->setPressed(false);

        //=== handle mouse up on a button

        if (m_homeFormButton->contains(MOUSE_POSITION) )
        {
            stop_leaderboard = true;
        }
        if (m_clearLbRectButton->contains(MOUSE_POSITION) )
        {
            m_leaderboard->getDataBase()->clearLeaderboard();
            m_textHandler->syncMenuLeaderboardText();
        }
    }
    return stop_leaderboard;
}
