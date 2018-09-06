#include "LeaderboardView.h"

//------------------------------------------------
//          CONSTRUCTORS / DESTRUCTOR
//------------------------------------------------

/**
 * Constructs the leaderboard view
 * with the window, the text manager and its model counterpart
 *
 * @param window the app window
 * @param textManager the text manager
 * @param leaderboardModel the leaderboard model counterpart
 *
 * @author Arthur
 * @date 21/05/16 - 02/01/18
 */
LeaderboardView::LeaderboardView(sf::RenderWindow* window, AppTextManager* textManager,
                                 LeaderboardModel* leaderboardModel) :
        AbstractView(window, textManager), m_leaderboard{leaderboardModel}
{
    //=== Init images and text

    loadSprites();

    textManager->initMenuLeaderboardText();

    //=== Init confirm dialog

    //TODO: No dialog init at startup
    m_confirmDialog = new mdsf::Dialog(m_width / 2 - 140, m_height / 2 - 120, 280, 200, "confirm_leaderboard_delete");
    m_confirmDialog->hide();
    DialogBuilder::retrieveCorrespondingStrings(m_confirmDialog);
}


/**
 * Destructor
 * @author Arthur
 * @date 21/05/16 - 02/01/18
 */
LeaderboardView::~LeaderboardView()
{
    delete m_homeFormButton;
    delete m_clearLeaderboardRaisedButton;
    delete m_confirmDialog;
}


//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Loads all sprites used by the leaderboard screen
 *
 * @author Arthur
 * @date 20/05/16 - 04/01/18
 */
void LeaderboardView::loadSprites()
{
    //=== Initialize CLEAR button

    std::vector<sf::IntRect> clipRectClear;
    clipRectClear.emplace_back(RAISED_BUTTON_DEFAULT);
    clipRectClear.emplace_back(RAISED_BUTTON_PRESSED);
    m_clearLeaderboardRaisedButton = new mdsf::Button(m_width / 2 - 75, 540, 150, BUTTON_HEIGHT,
                                                      "leaderboard_clear_button", RECT_BUTTONS_IMAGE, clipRectClear);
    m_clearLeaderboardRaisedButton->retrieveAndSyncLabel(LocalizationManager::fetchLocalizedString);
    m_clearLeaderboardRaisedButton->setColor(mdsf::Color::MaterialRed);

    //=== Initialize HOME form button

    std::vector<sf::IntRect> clipRectHome;
    clipRectHome.emplace_back(0, 50, 50, 50);
    clipRectHome.emplace_back(51, 50, 50, 50);
    m_homeFormButton = new mdsf::Button(10, 10, 50, 50, SHAPE_BUTTONS_IMAGE, clipRectHome);
}


/**
 * Synchronizes leaderboard elements
 *
 * @author Arthur
 * @date 20/05/16 - 27/12/17
 */
void LeaderboardView::synchronize()
{
    m_homeFormButton->sync();
    m_homeFormButton->resize(SHAPE_BUTTONS_SIZE);
    m_clearLeaderboardRaisedButton->sync();

    m_textManager->syncMenuLeaderboardText();
}


/**
 * Draws leaderboard elements on the window
 *
 * @author Arthur
 * @date 21/05/16 - 02/01/18
 */
void LeaderboardView::draw() const
{
    m_window->clear(AppColor::CoalMine);

    //=== Graphic Elements drawing

    m_window->draw(*m_homeFormButton);
    m_clearLeaderboardRaisedButton->draw(m_window);
    m_confirmDialog->draw(m_window);

    //=== Text Drawing

    m_textManager->drawMenuLeaderboardText(m_window);

    m_window->display();
}


/**
 * Handles the user interaction events (mouse, keyboard, title bar buttons)
 *
 * @param event sfml event object
 * @return true if app state is unchanged
 *
 * @author Arthur
 * @date 21/05/16 - 02/01/17
 */
bool LeaderboardView::handleEvents(sf::Event event)
{
    if (MOUSE_LEFT_PRESSED_EVENT) {
        if (m_homeFormButton->contains(MOUSE_POSITION)) {
            m_homeFormButton->setPressed(true);
        }

        if (!m_confirmDialog->isVisible()) {
            if (m_clearLeaderboardRaisedButton->contains(MOUSE_POSITION)) {
                m_clearLeaderboardRaisedButton->setPressed(true);
            }
        }
    }

    if (event.type == sf::Event::MouseButtonReleased) {
        //=== Reset buttons

        m_homeFormButton->setPressed(false);
        m_clearLeaderboardRaisedButton->setPressed(false);

        //=== handle mouse up on a button

        if (!m_confirmDialog->isVisible()) {
            if (m_homeFormButton->contains(MOUSE_POSITION)) {
                m_leaderboard->quit();
                return false;
            }

            if (m_clearLeaderboardRaisedButton->contains(MOUSE_POSITION)) {
                m_confirmDialog->show();
            }
        } else {
            if (m_confirmDialog->getOkButtonText().contains(MOUSE_POSITION)) {
                m_confirmDialog->hide();
                m_leaderboard->getAppCore()->clearLeaderboard();
                m_textManager->updateWholeStandaloneTextContent();
                m_textManager->syncMenuLeaderboardText();
            } else if (m_confirmDialog->getCancelButtonText().contains(MOUSE_POSITION)
                    || !m_confirmDialog->contains(MOUSE_POSITION)) {
                m_confirmDialog->hide();
            }
        }
    }

    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) {
        m_confirmDialog->hide();
    }

    return true;
}
