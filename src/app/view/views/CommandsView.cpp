#include "CommandsView.h"

//------------------------------------------------
//          CONSTRUCTORS / DESTRUCTOR
//------------------------------------------------

/**
 * Constructs the commands view
 * with the window, the text manager and its model counterpart
 *
 * @param window the app window
 * @param textManager the text manager
 * @param commandsModel the commands model counterpart
 *
 * @author Arthur
 * @date 24/01/17 - 29/01/17
 */
CommandsView::CommandsView(sf::RenderWindow* window, AppTextManager* textManager, CommandsModel* commandsModel) :
        AbstractView(window, textManager), m_commands{commandsModel}
{
    loadSprites();
}


/**
 * Destructor
 * @author Arthur
 * @date 24/01/17 - 05/02/18
 */
CommandsView::~CommandsView()
{
    delete m_homeButton;
}


//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Loads all sprites used by the commands screen
 *
 * @author Arthur
 * @date 24/01/17 - 11/09/18
 */
void CommandsView::loadSprites()
{
    //=== Initialize HOME buttons

    std::vector<sf::IntRect> clipRectHome;
    clipRectHome.emplace_back(HOME_BUTTON_CLIP_DEFAULT);
    clipRectHome.emplace_back(HOME_BUTTON_CLIP_PRESSED);
    m_homeButton = new mdsf::Button(10, 10, ORIGINAL_HOME_BUTTONS_SIZE, ORIGINAL_HOME_BUTTONS_SIZE,
                                        SHAPE_BUTTONS_IMAGE, clipRectHome);
}


/**
 * Synchronizes commands elements
 *
 * @author Arthur
 * @date 24/01/17 - 11/09/18
 */
void CommandsView::synchronize()
{
    m_homeButton->sync();
    m_homeButton->resize(HOME_BUTTONS_SIZE);

    m_textManager->syncMenuCommandsText();
}


/**
 * Draws commands elements on the window
 *
 * @author Arthur
 * @date 24/01/17 - 05/02/18
 */
void CommandsView::draw() const
{
    m_window->clear(AppColor::CoalMine);

    //=== Graphic Elements drawing

    m_window->draw(*m_homeButton);

    //=== Text Drawing

    m_textManager->drawMenuCommandsText(m_window);

    m_window->display();
}


/**
 * Handles the user interaction events (mouse, keyboard, title bar buttons)
 *
 * @param event sfml event object
 * @return true if app state is unchanged
 *
 * @author Arthur
 * @date 24/01/17 - 26/12/17
 */
bool CommandsView::handleEvents(sf::Event event)
{
    if (MOUSE_LEFT_PRESSED_EVENT) {
        if (m_homeButton->contains(MOUSE_POSITION)) {
            m_homeButton->setPressed(true);
        }
    }

    if (event.type == sf::Event::MouseButtonReleased) {
        //=== Reset buttons

        m_homeButton->setPressed(false);


        //=== handle mouse up on a button

        if (m_homeButton->contains(MOUSE_POSITION)) {
            return false;
        }
    }

    return true;
}
