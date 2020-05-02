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
    m_goHomeButton->sync();
    m_goHomeButton->resize(HOME_BTN_SIZE);
    m_goHomeButton->setPosition(0.033f * m_width, 0.89f * m_height);
    m_goHomeButton->syncLabelPosition();

    m_coinSprite->sync();
    m_coinSprite->resize(RESULTS_COIN_SIZE);
    m_coinSprite->setPosition(0.43f * m_width, 0.936f * m_height);

    m_restartButton->sync();
    m_restartButton->resize(HOME_BTN_SIZE);
    m_restartButton->setPosition(0.933f * m_width, 0.89f * m_height);
    m_restartButton->setLabelPosition(mdsf::LabelPosition::LEFT);
    m_restartButton->syncLabelPosition();

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

    m_restartButton->draw(m_window);
    m_goHomeButton->draw(m_window);
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
 * @date 26/12/17 - 13/01/19
 */
bool GameView::handleGameOverEvents(const sf::Event& event)
{
    if (EventUtils::wasMouseLeftPressed(event)) {
        m_restartButton->setPressed(EventUtils::isMouseInside(*m_restartButton, event));
        m_goHomeButton->setPressed(EventUtils::isMouseInside(*m_goHomeButton, event));
        m_saveScoreButton->setPressed(EventUtils::isMouseInside(*m_saveScoreButton, event));
    }

    if (EventUtils::wasMouseReleased(event)) {
        m_restartButton->setPressed(false);
        m_goHomeButton->setPressed(false);
        m_saveScoreButton->setPressed(false);

        if (EventUtils::isMouseInside(*m_restartButton, event)) {
            return false;
        } else if (EventUtils::isMouseInside(*m_goHomeButton, event)) {
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
