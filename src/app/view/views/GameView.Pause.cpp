#include "GameView.h"

//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Updates elements of a paused game
 *
 * @author Arthur
 * @date 6/03/16 - 02/05/2020
 */
void GameView::updatePausedGameElements()
{
    m_resumeButton->sync();
    m_restartButton->sync();
    m_goHomeButton->sync();
    m_musicButton->setToggled(m_game->isMusicEnabled());
    m_musicButton->sync();
    m_coinSprite->sync();
    m_coinSprite->resize(INGAME_COIN_SIZE);
    m_coinSprite->setPosition(0.033f * m_width, 0.16f * m_height);
    m_stdEnemySprite->setPosition(0.033f * m_width, 0.225f * m_height);
    m_stdEnemySprite->sync();
    m_stdEnemySprite->resize(ENEMY_SIZE);
}


/**
 * Draws elements of a paused game
 *
 * @author Arthur
 * @date 24/12/17
 */
void GameView::drawPausedGame() const
{
    //=== Background drawing & Sprites drawing

    m_window->draw(*m_pauseBackground);
    m_window->draw(*m_distanceIcon);
    m_window->draw(*m_coinSprite);
    m_window->draw(*m_stdEnemySprite);

    m_window->draw(*m_resumeButton);
    m_window->draw(*m_restartButton);
    m_window->draw(*m_goHomeButton);
    m_window->draw(*m_musicButton);

    //=== Standalone Text drawing

    m_textManager->drawGamePausedText(m_window);
}


/**
 * Handle paused game events
 *
 * @param event sfml event object
 * @return true if app state is unchanged
 *
 * @author Arthur
 * @date 26/12/17 - 13/01/19
 */
bool GameView::handlePausedGameEvents(const sf::Event& event)
{
    if (EventUtils::wasMouseLeftPressed(event)) {
        m_resumeButton->setPressed(EventUtils::isMouseInside(*m_resumeButton, event));
        m_restartButton->setPressed(EventUtils::isMouseInside(*m_restartButton, event));
        m_goHomeButton->setPressed(EventUtils::isMouseInside(*m_goHomeButton, event));
        m_musicButton->setPressed(EventUtils::isMouseInside(*m_musicButton, event));
    }

    if (EventUtils::wasMouseReleased(event)) {
        m_resumeButton->setPressed(false);
        m_restartButton->setPressed(false);
        m_goHomeButton->setPressed(false);
        m_musicButton->setPressed(false);

        if (EventUtils::isMouseInside(*m_resumeButton, event)) {
            m_game->setGameState(RUNNING_SLOWLY);
            if (m_gameThemeMusic.getStatus() == sf::Music::Status::Paused) {
                m_gameThemeMusic.play();
            }
        } else if (EventUtils::isMouseInside(*m_restartButton, event)) {
            return false;
        } else if (EventUtils::isMouseInside(*m_goHomeButton, event)) {
            m_game->setAppState(MENU);
            return false;
        } else if (EventUtils::isMouseInside(*m_musicButton, event)) {
            m_game->toggleGameMusic();
            handleMusic();
        }
    }
    return true;
}
