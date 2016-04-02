/* Copyright (C) 2016 Jolivet Arthur & Laronze Florian

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef TEXT_H
#define TEXT_H

#include "GameModel.h"
#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"


/********************************************
    Constant Variables
********************************************/
const std::string OLIVE_FONT = "Fonts/Antique_Olive.ttf";
const std::string ROBOTO_FONT = "Fonts/Roboto_Condensed.ttf";

/********************************************
    Text Class
*********************************************
    Arthur : 02/04
*********************************************/
class Text
{
    public:
    //=== CTORs / DTORs
    Text();
    ~Text();

    //=== GETTERS
    sf::Text getPauseResumeText();
    sf::Text getRestartText();
    sf::Text getHomeText();

    //=== METHODS
    void loadText();
    void syncMenuText(int width, int height);
    void syncGameText(GameModel *gameModel);
    void syncPauseText(GameModel *gameModel);
    void syncEndText(GameModel *gameModel);
    void drawMenuText(sf::RenderWindow *window);
    void drawGameText(sf::RenderWindow *window);
    void drawPauseText(sf::RenderWindow *window);
    void drawEndText(sf::RenderWindow *window);

private:
    //=== ATTRIBUTES
    sf::Font *m_font;

    //Menu Text
    sf::Text m_playButtonText;
    sf::Text m_quitButtonText;
    //Game Text
    sf::Text m_distanceText;
    sf::Text m_playerLifeLabel;
    //Pause Text
    sf::Text m_pauseResumeLabel;
    sf::Text m_restartLabel;
    sf::Text m_homeLabel;
    sf::Text m_CoinsCollectedNumberText;
    //End Text
    sf::Text m_endTitleLabel;
    sf::Text m_gameSpeedmultiplicatorLabel;
    sf::Text m_gameSpeedmultiplicatorText;
    sf::Text m_distanceLabel;
    sf::Text m_CoinsCollectedNumberLabel;
    sf::Text m_scoreLabel;
    sf::Text m_scoreText;
};

#endif // TEXT_H
