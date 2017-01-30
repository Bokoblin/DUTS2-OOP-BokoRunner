#include "CommandsView.h"

using namespace std;

/**
 * Parameterized Constructor
 * @author Arthur
 * @date 24/01/17 - 29/01/17
 */
CommandsView::CommandsView(sf::RenderWindow *window, TextHandler *textHandler, Commands *commandsModel) :
        AbstractView(window, textHandler), m_commands{commandsModel}
{
    loadImages();
}


/**
 * Destructor
 * @author Arthur
 * @date 24/01/17
 */
CommandsView::~CommandsView()
{
    delete m_commandSprite;
    delete m_homeFormButton;
}


/**
 * Image Loading
 * @author Arthur
 * @date 24/01/17
 */
void CommandsView::loadImages()
{
    //=== Initialize COIN Sprite

    m_commandSprite = new GraphicElement(m_width/2-220, m_height/2-150, 440, 300);
    if ( m_commands->getDataBase()->getLanguage() == "en")
        m_commandSprite->setTextureFromImage(COMMAND_EN_IMAGE);
    else if ( m_commands->getDataBase()->getLanguage() == "fr")
        m_commandSprite->setTextureFromImage(COMMAND_FR_IMAGE);
    else if ( m_commands->getDataBase()->getLanguage() == "es")
        m_commandSprite->setTextureFromImage(COMMAND_ES_IMAGE);

    //=== Initialize HOME form buttons

    std::vector<sf::IntRect> clipRectHome;
    clipRectHome.push_back(sf::IntRect( 0, 50, 50, 50));
    clipRectHome.push_back(sf::IntRect( 51, 50, 50, 50));
    m_homeFormButton = new Button(10, 10, 50, 50, SHAPE_BUTTONS_IMAGE, clipRectHome);
}






/**
 * Synchronization function
 * @author Arthur
 * @date 24/01/17
 */
void CommandsView::synchronize()
{
    m_homeFormButton->sync();
    m_homeFormButton->resize(FORM_BUTTONS_SIZE);
}


/**
 * Menu View Drawing
 * @author Arthur
 * @date 24/01/17
 */
void CommandsView::draw() const
{
    m_window->clear(MINE_GREY_COLOR);

    //=== Graphic Elements drawing

    m_window->draw(*m_homeFormButton);
    m_window->draw(*m_commandSprite);

    m_window->display();
}


/**
 * Events treating
 * @author Arthur
 * @date 24/01/17
 */
bool CommandsView::treatEvents(sf::Event event)
{
    bool stop_command = false;

    if (MOUSE_LEFT_PRESSED_EVENT)
    {
        if (m_homeFormButton->contains(MOUSE_POSITION))
            m_homeFormButton->setPressed(true);
    }

    if (event.type == sf::Event::MouseButtonReleased)
    {
        //=== Reset buttons

        m_homeFormButton->setPressed(false);


        //=== handle mouse up on a button

        if ( m_homeFormButton->contains(MOUSE_POSITION) )
            stop_command = true;
    }

    return stop_command;
}
