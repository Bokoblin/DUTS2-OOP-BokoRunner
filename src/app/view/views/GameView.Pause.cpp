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
    m_resumeGameButton->sync();
    m_resumeGameButton->resize(PAUSE_BUTTONS_SIZE);
    m_restartGameButton->sync();
    m_restartGameButton->resize(PAUSE_BUTTONS_SIZE);
    m_goToHomeButton->sync();
    m_goToHomeButton->resize(PAUSE_BUTTONS_SIZE);
    m_controlMusicButton->setToggled(m_game->isMusicEnabled());
    m_controlMusicButton->sync();
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

    m_resumeGameButton->draw(m_window);
    m_restartGameButton->draw(m_window);
    m_goToHomeButton->draw(m_window);
    m_controlMusicButton->draw(m_window);

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
        m_resumeGameButton->setPressed(EventUtils::isMouseInside(*m_resumeGameButton, event));
        m_restartGameButton->setPressed(EventUtils::isMouseInside(*m_restartGameButton, event));
        m_goToHomeButton->setPressed(EventUtils::isMouseInside(*m_goToHomeButton, event));
        m_controlMusicButton->setPressed(EventUtils::isMouseInside(*m_controlMusicButton, event));
    }

    if (EventUtils::wasMouseReleased(event)) {
        m_resumeGameButton->setPressed(false);
        m_restartGameButton->setPressed(false);
        m_goToHomeButton->setPressed(false);
        m_controlMusicButton->setPressed(false);

        if (EventUtils::isMouseInside(*m_resumeGameButton, event)) {
            m_game->setGameState(RUNNING_SLOWLY);
            if (m_gameThemeMusic.getStatus() == sf::Music::Status::Paused) {
                m_gameThemeMusic.play();
            }
        } else if (EventUtils::isMouseInside(*m_restartGameButton, event)) {
            return false;
        } else if (EventUtils::isMouseInside(*m_goToHomeButton, event)) {
            m_game->setAppState(MENU);
            return false;
        } else if (EventUtils::isMouseInside(*m_controlMusicButton, event)) {
            m_game->toggleGameMusic();
            handleMusic();
        }
    }
    return true;
}
