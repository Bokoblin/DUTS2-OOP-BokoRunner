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
 * @date 24/01/17 - 17/09/18
 */
void CommandsView::loadSprites()
{
    //=== Initialize HOME button

    m_homeButton = new mdsf::RaisedButton(10, 10, DEFAULT_HOME_SIZE, DEFAULT_HOME_SIZE, "", HOME_IMAGE);
    m_homeButton->resize(HOME_BUTTON_SIZE, HOME_BUTTON_SIZE);
}


/**
 * Synchronizes commands elements
 *
 * @author Arthur
 * @date 24/01/17 - 22/09/18
 */
void CommandsView::synchronize()
{
    m_homeButton->sync();

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

    m_homeButton->draw(m_window);

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
 * @date 24/01/17 - 30/10/18
 */
bool CommandsView::handleEvents(sf::Event event)
{
    if (EventUtils::wasMouseLeftPressed(event)) {
        m_homeButton->setPressed(EventUtils::isMouseInside(*m_homeButton, event));
    }

    if (EventUtils::wasMouseReleased(event)) {
        //=== Reset buttons

        m_homeButton->setPressed(false);


        //=== handle mouse up on a button

        if (EventUtils::isMouseInside(*m_homeButton, event)) {
            return false;
        }
    }

    return true;
}
