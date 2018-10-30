#include "GameView.h"

//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Updates elements of a game over
 *
 * @author Arthur
 * @date 6/03/16 - 11/09/18
 */
void GameView::updateGameOverElements()
{
    m_goToHomeButton->sync();
    m_goToHomeButton->resize(HOME_BUTTON_SIZE);
    m_goToHomeButton->setPosition(0.033f * m_width, 0.89f * m_height);
    m_goToHomeButton->syncLabelPosition();

    m_coinSprite->sync();
    m_coinSprite->resize(RESULTS_COIN_SIZE);
    m_coinSprite->setPosition(0.43f * m_width, 0.936f * m_height);

    m_restartGameButton->sync();
    m_restartGameButton->resize(HOME_BUTTON_SIZE);
    m_restartGameButton->setPosition(0.933f * m_width, 0.89f * m_height);
    m_restartGameButton->setLabelPosition(mdsf::LabelPosition::LEFT);
    m_restartGameButton->syncLabelPosition();

    m_saveScoreButton->sync();
}


/**
 * Draws elements of a game over
 *
 * @author Arthur
 * @date 24/12/17
 */
void GameView::drawGameOver() const
{
    //=== Background drawing & Buttons drawing

    m_window->draw(*m_endBackground);
    m_window->draw(*m_coinSprite);

    m_restartGameButton->draw(m_window);
    m_goToHomeButton->draw(m_window);
    m_saveScoreButton->draw(m_window);

    //=== Standalone Text drawing

    m_textManager->drawGameOverText(m_window);
}


/**
 * Handle game over events
 *
 * @param event sfml event object
 * @return true if app state is unchanged
 *
 * @author Arthur
 * @date 26/12/17 - 30/10/18
 */
bool GameView::handleGameOverEvents(sf::Event event)
{
    if (EventUtils::wasMouseLeftPressed(event)) {
        m_restartGameButton->setPressed(EventUtils::isMouseInside(*m_restartGameButton, event));
        m_goToHomeButton->setPressed(EventUtils::isMouseInside(*m_goToHomeButton, event));
        m_saveScoreButton->setPressed(EventUtils::isMouseInside(*m_saveScoreButton, event));
    }

    if (EventUtils::wasMouseReleased(event)) {
        m_restartGameButton->setPressed(false);
        m_goToHomeButton->setPressed(false);
        m_saveScoreButton->setPressed(false);

        if (EventUtils::isMouseInside(*m_restartGameButton, event)) {
            return false;
        } else if (EventUtils::isMouseInside(*m_goToHomeButton, event)) {
            m_game->setAppState(MENU);
            return false;
        } else if (EventUtils::isMouseInside(*m_saveScoreButton, event)) {
            m_saveScoreButton->hide();
            m_game->saveCurrentGame();
            PersistenceManager::updatePersistence();
        }
    }
    return true;
}
